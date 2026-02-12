function(add_auto_executable target_name src_dir header_dir_list)
    #Récupère tous les fichiers sources (.cpp, .c) dans src_dir et ses sous-dossiers
    file(GLOB_RECURSE TARGET_SOURCES
        CONFIGURE_DEPENDS
        "${src_dir}/*.cpp"
        "${src_dir}/*.c"
    )

    list(APPEND TARGET_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp")

    add_executable(${target_name} ${TARGET_SOURCES})

    #Récupère tous les dossiers de headers et ajoute comme include path
    foreach(hdir IN LISTS header_dir_list)
        # ajoute le dossier lui-même
        target_include_directories(${target_name} PRIVATE ${hdir})

        # cherche tous les sous-dossiers et les ajoute aussi
        file(GLOB_RECURSE SUBHEADER_DIRS RELATIVE ${hdir} ${hdir}/*)
        foreach(subdir ${SUBHEADER_DIRS})
            if(IS_DIRECTORY "${hdir}/${subdir}")
                target_include_directories(${target_name} PRIVATE "${hdir}/${subdir}")
            endif()
        endforeach()
    endforeach()

    #Output binaire
    set_target_properties(${target_name} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    )

    message(STATUS "Target '${target_name}' will compile sources from ${src_dir}")
endfunction()

