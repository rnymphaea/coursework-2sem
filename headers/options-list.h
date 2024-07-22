#ifndef CW_PROB_OPTS_H
#define CW_PROB_OPTS_H

const struct option longOptions[] = {
        { "help", no_argument, NULL, 'h' },
        { "output", required_argument, NULL, 'o' },
        { "info", no_argument, NULL, 400 },
        { "input", required_argument, NULL, 'i' },
        { "rgbfilter", no_argument, NULL, 'f' },
        { "component_name", required_argument, NULL, 100 },
        { "component_value", required_argument, NULL, 101 },
        { "square", no_argument, NULL, 's' },
        { "left_up", required_argument, NULL, 200 },
        { "side_size", required_argument, NULL, 201 },
        { "thickness", required_argument, NULL, 't' },
        { "color", required_argument, NULL, 'c' },
        { "fill", no_argument, NULL, 203 },
        { "fill_color", required_argument, NULL, 204 },
        { "exchange", no_argument, NULL, 'x' },
        { "right_down", required_argument, NULL, 300 },
        { "exchange_type", required_argument, NULL, 301 },
        { "freq_color", no_argument, NULL, 500 },
        { "outside_ornament", no_argument, NULL, 700 },
        { NULL, 0, NULL, 0}
};

char * shortOptions = "ho:i:fst:c:x";

#endif //CW_PROB_OPTS_H
