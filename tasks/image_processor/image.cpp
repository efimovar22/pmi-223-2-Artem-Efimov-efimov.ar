#include "image.h"

Image::Image(size_t height, size_t width)
    : height_(height), width_(width), colors_(height_, std::vector<Color>(width)) {
}
Image::Image(const Image& other) : height_(other.height_), width_(other.width_), colors_(other.GetColorsVector()) {
}

Image::Image(const std::vector<std::vector<Color>>& other)
    : height_(other.size()), width_(other[0].size()), colors_(other) {
}

size_t Image::Height() const {
    return height_;
}

size_t Image::Width() const {
    return width_;
}

std::vector<Color>& Image::operator[](ssize_t i) {
    return colors_[i];
}

std::vector<Color>& Image::operator[](size_t i) {
    return colors_[i];
}

const std::vector<Color>& Image::operator[](size_t i) const {
    return colors_[i];
}

const std::vector<std::vector<Color>>& Image::GetColorsVector() const {
    return colors_;
}

Color& Image::GetColor(size_t x, size_t y) {
    if (x > height_ || y > width_) {
        throw std::invalid_argument("Wrong parameters");
    }
    return colors_[x][y];
}

const Color& Image::GetColor(size_t x, size_t y) const {
    if (x > height_ || y > width_) {
        throw std::invalid_argument("Wrong parameters");
    }
    return colors_[x][y];
}

void Image::MakeColor(size_t x, size_t y, Color color) {
    if (x > height_ || y > width_) {
        throw std::invalid_argument("Wrong parameters");
    }
    colors_[x][y] = color;
}

#pragma pack(push, 1)
struct BmpHeader {
    char id[2] = {'B', 'M'};
    uint32_t file_size;
    char unused[4] = "\0\0\0";
    uint32_t data_offset;
};

struct DIBHeader {
    uint32_t header_size;
    int32_t width;
    int32_t height;
    uint16_t number_of_planes;
    uint16_t bits_per_pixel;
    uint32_t compression;
    uint32_t bitmap_size;
    uint32_t resolution_horizontal = 0;
    uint32_t resolution_vertical = 0;
    uint32_t colors_in_palette = 0;
    uint32_t important_colors = 0;
};
#pragma pack(pop)

void Image::Read(const char* path) {
    const auto dev = 255.0f;
    std::ifstream f;
    f.open(path, std::ios::in | std::ios::binary);

    if (!f.is_open()) {
        std::cout << "File could not be opened" << std::endl;
        return;
    }

    //    const size_t fileHeaderSize = sizeof(BmpHeader);
    //    const size_t informationHeaderSize = sizeof(DIBHeader);

    BmpHeader file_header;
    f.read(reinterpret_cast<char*>(&file_header), sizeof(BmpHeader));

    if (file_header.id[0] != 'B' || file_header.id[1] != 'M') {
        std::cout << "The specified path is not a bitmap image" << std::endl;
        return;
    }

    DIBHeader info_header;
    f.read(reinterpret_cast<char*>(&info_header), sizeof(info_header));

    width_ = info_header.width;
    height_ = info_header.height;

    colors_ = std::vector(height_, std::vector<Color>(width_));

    const int padding_amount = static_cast<int>((4 - (width_ * 3) % 4) % 4);
    for (size_t y = 0; y < height_; ++y) {
        for (size_t x = 0; x < width_; ++x) {
            uint8_t color[3];
            f.read(reinterpret_cast<char*>(color), 3);
            colors_[y][x].Red = static_cast<float>(color[2]) / dev;
            colors_[y][x].Green = static_cast<float>(color[1]) / dev;
            colors_[y][x].Blue = static_cast<float>(color[0]) / dev;
        }
        f.ignore(padding_amount);
    }
    std::cout << "File read" << std::endl;
}

void Image::Export(const char* path) const {
    std::ofstream f(path, std::ios::out | std::ios::binary);
    if (!f.is_open()) {
        std::cout << "File could not be opened\n";
        return;
    }
    const auto dev = 255.0f;
    const size_t padding_amount = static_cast<int>((4 - (width_ * 3) % 4) % 4);

    const size_t file_size = sizeof(BmpHeader) + sizeof(DIBHeader) + width_ * height_ * 3 + padding_amount * width_;
    const auto tw_f = 24;
    BmpHeader file_header = {.file_size = static_cast<uint32_t>(file_size),
                             .data_offset = sizeof(BmpHeader) + sizeof(DIBHeader)};
    DIBHeader info_header = {.header_size = sizeof(DIBHeader),
                             .width = static_cast<int32_t>(width_),
                             .height = static_cast<int32_t>(height_),
                             .number_of_planes = 1,
                             .bits_per_pixel = tw_f,
                             .compression = 0,
                             .bitmap_size = static_cast<uint32_t>(file_size - sizeof(BmpHeader) - sizeof(DIBHeader))};

    f.write(reinterpret_cast<char*>(&file_header), sizeof(BmpHeader));
    f.write(reinterpret_cast<char*>(&info_header), sizeof(DIBHeader));

    for (size_t y = 0; y < height_; ++y) {
        for (size_t x = 0; x < width_; ++x) {
            unsigned char r = static_cast<unsigned char>(GetColor(y, x).Red * dev);
            unsigned char g = static_cast<unsigned char>(GetColor(y, x).Green * dev);
            unsigned char b = static_cast<unsigned char>(GetColor(y, x).Blue * dev);

            unsigned char color[] = {b, g, r};

            f.write(reinterpret_cast<char*>(color), 3);
        }
        f.write("\0\0\0", static_cast<std::streamsize>(padding_amount));
    }
    f.close();
    std::cout << "File created\n";
}