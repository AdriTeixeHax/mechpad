cmake_minimum_required(VERSION 4.0)

idf_component_register(SRCS "hello_world_main.c"
                    PRIV_REQUIRES spi_flash
                    INCLUDE_DIRS "")
