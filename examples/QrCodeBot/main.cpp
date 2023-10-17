#include <csignal> // std::signal
#include <string>
#include <tgbotxx/tgbotxx.hpp> // tgbotxx
using namespace tgbotxx;

#include <BarcodeFormat.h>
#include <BitMatrix.h>
#include <CharacterSet.h>
#include <GTIN.h>
#include <MultiFormatWriter.h>
#include <ReadBarcode.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

class QrCodeBot : public Bot {
  public:
    QrCodeBot(const std::string& token) : Bot(token) {}

  private:
    void onStart() override {
      // Drop pending updates
      api()->deleteWebhook(true);

      // Register my commands
      Ptr<BotCommand> startCmd(new BotCommand());
      startCmd->command = "/start";
      startCmd->description = "Start interacting with the bot";
      api()->setMyCommands({startCmd});

      std::cout << "Bot " << api()->getMe()->username << " Started\n";
    }

    void onStop() override {
      std::cout << "\nStopping Bot. Please wait...\n";
    }

    void onNonCommandMessage(const Ptr<Message>& message) override try {
      if (not message->photo.empty()) { // Did user send a photo ?
        // Convert QrCode image to text
        api()->sendChatAction(message->chat->id, "typing");
        std::string qrCodeText = extractTextFromQrCodeImage(message->photo);
        api()->sendMessage(message->chat->id, qrCodeText);
      } else if (not message->text.empty()) { // Did user send a text ?
        // Convert text to QrCode image
        api()->sendChatAction(message->chat->id, "upload_photo");
        cpr::File qrCodePhoto = convertTextToQrCodeImage(message->text);
        api()->sendPhoto(message->chat->id, qrCodePhoto);
      }
    } catch (const std::exception& e) {
      std::cerr << e.what() << std::endl;
      api()->sendMessage(message->chat->id, "Internal error");
    }

    void onCommand(const Ptr<Message>& message) override {
      if (message->text == "/start") {
        api()->sendMessage(message->chat->id, "Welcome to QrCodeBot! Please send a text to generate a QrCode Image, or send a QrCode Image to extract text from it.");
      }
    }

  protected:
    /// Extracts UTF-8 text from a QR Code Image
    /// @param photos multiple resolution photo sizes from Message
    /// @returns Extracted UTF-8 text from the QR Code image
    std::string extractTextFromQrCodeImage(const std::vector<Ptr<PhotoSize>>& photos) {
      // Get the highest resolution image (Telegram provides 4 resolutions of photo sent by user)
      const Ptr<PhotoSize>& photo = *std::max_element(photos.begin(), photos.end(), [](const Ptr<PhotoSize>& A, const Ptr<PhotoSize>& B) {
        return A->height < B->height && A->width < B->width;
      });

      // Download photo from Telegram servers
      Ptr<File> file = api()->getFile(photo->fileId);
      std::string bytes = api()->downloadFile(file->filePath, [](long total, long downloaded) -> bool {
        std::cout << "Downloading photo " << downloaded << '/' << total << " bytes     \r" << std::flush;
        return true;
      });
      std::cout << std::endl;

      // Save downloaded photo to ./photos/input/PHOTO.jpg
      fs::path photosDir = "photos/input";
      if (!fs::exists(photosDir)) fs::create_directories(photosDir);
      fs::path photoPath = photosDir / fs::path(file->filePath).filename();
      std::ofstream ofs{photoPath, std::ios::binary};
      ofs.write(bytes.data(), bytes.size());
      ofs.close();
      bytes.clear();

      // Load back image using stbi image
      int width{}, height{}, channels{};
      std::unique_ptr<stbi_uc, void (*)(void *)> buffer(stbi_load(photoPath.string().c_str(), &width, &height, &channels, 3), stbi_image_free);
      if (!buffer) {
        throw Exception("Failed to read image: " + photoPath.string());
      }

      // Decode qr code image
      ZXing::DecodeHints hints{};
      hints.setTextMode(ZXing::TextMode::HRI); // Human Readable Interpretation
      hints.setEanAddOnSymbol(ZXing::EanAddOnSymbol::Read);
      hints.setTryHarder(true);
      ZXing::ImageView image{buffer.get(), width, height, ZXing::ImageFormat::RGB};
      auto result = ZXing::ReadBarcode(image, hints);
      if (result.isValid()) {
        return result.text();
      }
      return ZXing::ToString(result.error());
    }

    /// Converts @text to a QR Code image
    /// @param text UTF-8 Text to convert
    /// @returns cpr::File filename of the generated image
    cpr::File convertTextToQrCodeImage(const std::string& text) {
      ZXing::MultiFormatWriter writer(ZXing::BarcodeFormat::QRCode);
      writer.setMargin(-1);
      writer.setEncoding(ZXing::CharacterSet::UTF8);
      ZXing::BitMatrix matrix = writer.encode(text, 128, 128);
      ZXing::Matrix<std::uint8_t> bitmap = ZXing::ToMatrix<std::uint8_t>(matrix);

      fs::path photosDir = "photos/output";
      if (!fs::exists(photosDir)) fs::create_directories(photosDir);
      fs::path photoPath = photosDir / (std::to_string(std::time(nullptr)) + ".jpg");
      // int success = stbi_write_png(filePath.c_str(), bitmap.width(), bitmap.height(), 1, bitmap.data(), 0);
      int success = stbi_write_jpg(photoPath.c_str(), bitmap.width(), bitmap.height(), 1, bitmap.data(), 0);
      if (!success) {
        throw Exception("Failed to write image: " + photoPath.string());
      }
      return cpr::File(photoPath.string());
    }
};


int main(int argc, const char *argv[]) {
  if (argc < 2) {
    std::cerr << "Usage:\nqrcode_bot \"BOT_TOKEN\"\n";
    return EXIT_FAILURE;
  }
  static std::unique_ptr<QrCodeBot> BOT;
  std::signal(SIGINT, [](int) { // Graceful Bot exit on CTRL+C
    if (BOT) {
      BOT->stop();
    }
    std::exit(EXIT_SUCCESS);
  });

  BOT = std::make_unique<QrCodeBot>(argv[1]);
  BOT->start();
  return EXIT_SUCCESS;
}
