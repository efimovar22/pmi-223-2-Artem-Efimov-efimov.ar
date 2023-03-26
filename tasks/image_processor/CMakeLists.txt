add_executable(
    image_processor
    image_processor.cpp
        color.h image.h image.cpp parser.h parser.cpp crop.h filter.h crop.cpp grayscale.cpp grayscale.h negative.h negative.cpp sharpening.h sharpening.cpp edge_detection.h gaussian_blur.h gaussian_blur.cpp color.cpp edge_detection.cpp filter_sequence.h filter_sequence.cpp my_filter.h my_filter.cpp)
