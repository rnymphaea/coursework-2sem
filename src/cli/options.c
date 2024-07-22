#include "../../headers/options.h"
#include "../../headers/options-list.h"

#define MAX_SIZE 4096

void handleInput(int argc, char * argv[]) {
    char * input = (char *)calloc(MAX_SIZE, sizeof(char));
    if (input == NULL) {
        printf("Error: cannot allocate memory!\n");
        exit(MEMORY_ALLOCATION_ERROR);
    }

    char * output = (char *)calloc(MAX_SIZE, sizeof(char));
    if (output == NULL) {
        printf("Error: cannot allocate memory!\n");
        exit(MEMORY_ALLOCATION_ERROR);
    }

    opterr = 0;
    int option_index;
    int res = getopt_long(argc, argv, shortOptions, longOptions, &option_index);

    int lx, ly;
    int thick;

    Tasks tasks;
    initTasks(&tasks);

    RGB color;
    RGBFilter rgbf;
    Square sq;
    Exchange ex;

    initSquare(&sq);
    initExchange(&ex);

    while (res != -1) {
        switch (res) {
            case 'h': // --help
                help();
                exit(0);

            case 'o': // --output
                strcpy(output, optarg);
                tasks.check_output++;
                break;

            case 'i': // --input
                input = optarg;
                tasks.check_input++;
                break;

            case 400: // --info
                tasks.check_info++;
                break;

            // --rgb-filter
            case 'f': // --rgbfilter
                tasks.check_rgbfilter++;
                break;

            case 100: // --component_name
                if (strcmp(optarg, "red") == 0) {
                    rgbf.componentName = red;
                } else if (strcmp(optarg, "green") == 0) {
                    rgbf.componentName = green;
                } else if (strcmp(optarg, "blue") == 0) {
                    rgbf.componentName = blue;
                } else {
                    printf("Error: incorrect component name!\n");
                    exit(INVALID_OPTION_ARG_ERROR);
                }
                tasks.check_component_name++;
                break;

            case 101: // --component_value
                if (checkNum(optarg)) {
                    int arg;
                    sscanf(optarg, "%d", &arg);
                    if (arg < 0 || arg > 255) {
                        printf("Error: component_value must be in [0; 255]!\n");
                        exit(INVALID_OPTION_ARG_ERROR);
                    }
                    rgbf.componentValue = arg;
                } else {
                    printf("Error: component value must be integer!\n");
                    exit(INVALID_OPTION_ARG_ERROR);
                }
                tasks.check_component_value++;
                break;


            case 'c': // --color
                if (checkColor(optarg)) {
                    sscanf(optarg, "%hhu.%hhu.%hhu", &color.r, &color.g, &color.b);
                } else {
                    printf("Error: invalid color!\n");
                    exit(INVALID_OPTION_ARG_ERROR);
                }

                tasks.check_color++;

                break;

            // square
            case 's': // --square
                tasks.check_square++;
                break;

            case 200: // --left_up
                if (checkCoordinates(optarg)) {
                    sscanf(optarg, "%d.%d", &lx, &ly);
                } else {
                    printf("Error: coordinates must match the format <x.y> where x and y are integers!\n");
                    exit(INVALID_OPTION_ARG_ERROR);
                }

                tasks.check_left_up++;
                break;

            case 201: // --side_size
                if (checkNum(optarg)) {
                    sscanf(optarg, "%u", &sq.sideSize);
                } else {
                    printf("Error: side size must be positive integer!\n");
                    exit(INVALID_OPTION_ARG_ERROR);
                }

                tasks.check_side_size++;
                break;

            case 't': // --thickness
                if (checkNum(optarg)) {
                    sscanf(optarg, "%d", &thick);
                    if (thick < 0) {
                        printf("Error: thickness must be positive integer!\n");
                        exit(INVALID_OPTION_ARG_ERROR);
                    }                
                    sscanf(optarg, "%u", &sq.thickness);
                }
                else {
                    printf("Error: thickness must be positive integer!\n");
                    exit(INVALID_OPTION_ARG_ERROR);
                }

                tasks.check_thickness++;
                break;

            case 203: // --fill
                tasks.check_fill++;
                sq.fill = 1;
                break;

            case 204: // --fill_color
                if (checkColor(optarg)) {
                    sscanf(optarg, "%hhu.%hhu.%hhu", &sq.fillColor.r, &sq.fillColor.g, &sq.fillColor.b);
                } else {
                    printf("Error: invalid fill color!\n");
                    exit(INVALID_OPTION_ARG_ERROR);
                }
                break;

            // exchange
            case 'x': // --exchange
                tasks.check_exchange++;
                break;

            case 300: // --right_down
                if (checkCoordinates(optarg)) {
                    sscanf(optarg, "%d.%d", &ex.rx, &ex.ry);
                } else {
                    printf("Error: coordinates must match the format <x.y> where x and y are integers!\n");
                    exit(INVALID_OPTION_ARG_ERROR);
                }
                break;

            case 301: // --exchange_type
                if (strcmp(optarg, "clockwise") == 0) {
                    ex.extype = clockwise;
                } else if (strcmp(optarg, "counterclockwise") == 0) {
                    ex.extype = counterclockwise;
                } else if (strcmp(optarg, "diagonals") == 0) {
                    ex.extype = diagonals;
                } else {
                    printf("Error: incorrect type of exchange!\n");
                    exit(INVALID_OPTION_ARG_ERROR);
                }
                break;

            // freq-color
            case 500: // freq_color
                tasks.check_freq_color++;
                break;

            case 700:
                tasks.check_ornament++;
                break;


            case '?':
                printf("Error: invalid option!\nTo see the help, use the option '--help ['-h']'\n");
                exit(INVALID_OPTION_ERROR);

            default:
                break;
        }
        res = getopt_long(argc, argv, shortOptions, longOptions, &option_index);
    }


    if (tasks.check_input == 0) {
        input = argv[argc - 1];
    }

    if (tasks.check_output == 0) {
        output = "out.bmp";
    }

    if (strcmp(input, output) == 0) {
        printf("Error: names of input and output files must be different!\n");
        exit(INVALID_OPTION_ARG_ERROR);
    }


    BitmapFileHeader bmfh;
    BitmapInfoHeader bmih;
    RGB ** rgb = readBMP(input, &bmfh, &bmih);

    if (!(checkBMP(&bmfh, &bmih))) {
        printf("Error: incorrect BMP format!\n");
        exit(INCORRECT_BMP_FORMAT_ERROR);
    }


    if (tasks.check_ornament) {
        if (tasks.check_thickness && tasks.check_color) {
            rgb = ornament(&bmih, rgb, color, thick);
        }
    }

    if (tasks.check_exchange) {
        
        ex.lx = lx;
        ex.ly = ly;
        if (ex.extype == undefined) {
            printf("Error: you didn't enter '--exchange_type' option!\n");
            exit(NO_REQUIRED_OPTIONS_ERROR);
        }
        rgb = exchange(rgb, bmih.height, bmih.width, ex);
  
    }


    if (tasks.check_square) {
        sq.x = lx;
        sq.y = ly;
        sq.color = color;
        if (tasks.check_color && tasks.check_left_up && tasks.check_thickness && tasks.check_side_size) {
            rgb = drawSquare(rgb, bmih.height, bmih.width, sq);
        } else {
            printf("Error: not enough options to draw square!\n");
            exit(NO_REQUIRED_OPTIONS_ERROR);
        }
    }


    if (tasks.check_rgbfilter) {
        if (tasks.check_component_name && tasks.check_component_value) {
            rgb = filter(rgb, bmih.height, bmih.width, rgbf.componentName, rgbf.componentValue);
        }
        else {
            printf("Error: not enough options to use rgb-filter!\n");
            exit(NO_REQUIRED_OPTIONS_ERROR);
        }
    }

    if (tasks.check_freq_color) {
        if (tasks.check_color) {
            rgb = processFreqColor(&bmih, rgb, color);
        }
        else {
            printf("Error: not enough options to replace freq. color!\n");
            exit(NO_REQUIRED_OPTIONS_ERROR);
        }
    }

    writeBMP(output, rgb, bmih.height, bmih.width, &bmfh, &bmih);

    if (tasks.check_info) {
        printFileHeader(bmfh);
        printInfoHeader(bmih);
    }

    for (unsigned int i = 0; i < bmih.height; i++) {
        free(rgb[i]);
    }
    free(rgb);

    free(output);
}

void initTasks(Tasks * tasks) {
    tasks -> check_info = 0;

    tasks -> check_rgbfilter = 0;
    tasks -> check_component_name = 0;
    tasks -> check_component_value = 0;

    tasks -> check_input = 0;

    tasks -> check_output = 0;

    tasks -> check_square = 0;
    tasks -> check_thickness = 0;
    tasks -> check_side_size = 0;
    tasks -> check_fill = 0;
    tasks -> check_fill_color = 0;

    tasks -> check_freq_color = 0;

    tasks -> check_color = 0;

    tasks -> check_exchange = 0;
    tasks -> check_right_down = 0;
    tasks -> check_exchange_type = 0;

    tasks -> check_left_up = 0;
    
    tasks -> check_ornament = 0;
}

int checkCoordinates(char * coords) {
    char * cpy = malloc(strlen(coords) + 1);
    if (cpy == NULL) {
        printf("Error: cannot allocate memory!\n");
        exit(MEMORY_ALLOCATION_ERROR);
    }

    strcpy(cpy, coords);
    int c = 0; // количество координат

    char * tmp = strtok(cpy, ".");
    while (tmp != NULL) {
        if (!(checkNum(tmp))) {
            free(cpy);
            return 0;
        }
        c++;
        tmp = strtok(NULL, ".");
    }

    free(cpy);
    return c == 2;
}

int checkNum(char * string) {
    int start = (string[0] == '-');
    for (size_t i = start; i < strlen(string); i++) {
        if (!(isdigit(string[i]))) {
            return 0;
        }
    }
    return 1;
}

int checkColor(char * color) {
    char * cpy = malloc(strlen(color) + 1);
    if (cpy == NULL) {
        printf("Error: cannot allocate memory!\n");
        exit(MEMORY_ALLOCATION_ERROR);
    }

    strcpy(cpy, color);
    int c = 0; // количество компонент (r g b)

    char * tmp = strtok(cpy, ".");
    while (tmp != NULL) {
        if (!(checkNum(tmp))) {
            free(cpy);
            return 0;
        } else {
            int component = atoi(tmp);
            if (component < 0 || component > 255) {
                free(cpy);
                return 0;
            }
        }
        tmp = strtok(NULL, ".");
        c++;
    }
    free(cpy);
    return c == 3;
}





