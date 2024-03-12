include(cmake/templates.cmake)

function(generate_tags_file)

    set(tags_file_name include/htmcxx/tags/tags.h)

    if(NOT EXISTS ${tags_file_name})
        file(WRITE ${tags_file_name} "${header_tags_template}")

        foreach(element ${tags_list})
            string(REPLACE "{template}" "${element}" class_generated "${tags_template}")
            file(APPEND ${tags_file_name} "${class_generated}")
        endforeach()

        file(APPEND ${tags_file_name} "${footer_tags_template}")
    endif()
endfunction()

function(generate_attributes_file)

    set(attributes_file_name include/htmcxx/attributes/attributes.h)

    if(NOT EXISTS ${attributes_file_name})
        file(WRITE ${attributes_file_name} "${header_attributes_template}")

        foreach(attribute ${attributes_list})
            string(REPLACE "{template}" "${attribute}" class_generated "${attributes_template}")
            file(APPEND ${attributes_file_name} "${class_generated}")
        endforeach()

        file(APPEND ${attributes_file_name} "${footer_attributes_template}")
    endif()
endfunction()
