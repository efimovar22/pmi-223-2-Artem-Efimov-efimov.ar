#include "image.h"
#include "parser.h"
#include "filter_sequence.h"
#include "grayscale.h"
#include "crop.h"
#include "gaussian_blur.h"
#include "negative.h"
#include "sharpening.h"
#include "edge_detection.h"
#include "filter.h"

int main(int argc, char** argv) {
    Image image;
    image.Read(argv[1]);
    FilterSequence filter_seq;
    for (const auto& [filter_name, filter_args] : ParseArgs(argc, argv)) {
        if (filter_name == "-gs") {
            filter_seq.AddFilter(new Grayscale());
        } else if (filter_name == "-neg") {
            filter_seq.AddFilter(new Negative());
        } else if (filter_name == "-crop") {
            if (filter_args.size() > 1) {
                filter_seq.AddFilter(new Crop(std::stoull(filter_args[0]), std::stoull(filter_args[1])));
            } else {
                std::cout << "Can not make";
                return 0;
            }
        } else if (filter_name == "-sharp") {
            filter_seq.AddFilter(new Sharpening());
        } else if (filter_name == "-blur") {
            if (!filter_args.empty()) {
                filter_seq.AddFilter(new GaussianBlur(std::stod(filter_args[0])));
            } else {
                std::cout << "Can not make";
                return 0;
            }
        } else if (filter_name == "-edge") {
            if (!filter_args.empty()) {
                filter_seq.AddFilter(new Grayscale());
                filter_seq.AddFilter(new EdgeDetection(std::stod(filter_args[0])));
            } else {
                std::cout << "Can not make";
                return 0;
            }
        }
    }
    image = filter_seq.Apply(image);
    image.Export(argv[2]);
    std::cout << argv[1];
    return 0;
}