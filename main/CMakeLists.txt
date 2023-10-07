idf_component_register(SRCS "main.c"
                    INCLUDE_DIRS "."
                    REQUIRES driver
                    soc
                    my_LCD16x2)
