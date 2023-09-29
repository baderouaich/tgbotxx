# From: https://github.com/gammasoft71/xtd/issues/13
# Thanks to @codeinred

set(remote_dependencies "")

# If ALWAYS_FETCH is ON, then find_or_fetch will always fetch any remote
# dependencies rather than using the ones provided by the system. This is
# useful for creating a static executable.
option(
        ALWAYS_FETCH
        "Tells find_or_fetch to always fetch packages"
        OFF)


include(FetchContent)
# find_or_fetch will search for a system installation of ${package} via
# find_package. If it fails to find one, it'll use FetchContent to download and
# build it locally.
function(find_or_fetch package repo tag)
    if (NOT ALWAYS_FETCH)
        find_package(${package} QUIET)
    endif()

    if (ALWAYS_FETCH OR NOT ${${package}_FOUND})
        message("Fetching dependency '${package}' from ${repo}")

        FetchContent_Declare(
                "${package}"
                GIT_REPOSITORY "${repo}"
                GIT_TAG "${tag}"
        )
        list(APPEND remote_dependencies "${package}")
        set (remote_dependencies  ${remote_dependencies} PARENT_SCOPE)
    else()
        message("Using system cmake package for dependency '${package}'")
    endif()
endfunction()