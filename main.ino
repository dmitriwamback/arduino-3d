#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1351.h>
#include <math.h>

#define SCREEN_WIDTH    128
#define SCREEN_HEIGHT   128

#define SCLOCK_PIN      13
#define MOST_PIN        11
#define RESET_PIN       3
#define DC_PIN          7
#define CS_PIN          10

#define HEX_COLOR_BLACK              0x0000
#define HEX_COLOR_WHITE              0xFFFF
#define HEX_COLOR_RED                0xF800
#define HEX_COLOR_GREEN              0x7E00
#define HEX_COLOR_BLUE               0x001F
#define HEX_COLOR_CYAN               0x07FF
#define HEX_COLOR_MAGENTA            0xF81F
#define HEX_COLOR_YELLOW             0xFFE0
#define HEX_COLOR_GREY               0x8410

Adafruit_SSD1351 displ = Adafruit_SSD1351(SCREEN_WIDTH, SCREEN_HEIGHT, &SPI, CS_PIN, DC_PIN, RESET_PIN);
float angle = 0;


class vec4 {
public:
    float x, y, z, w;
    static vec4 create(float x, float y, float z, float w);
};

vec4 vec4::create(float x, float y, float z, float w) {
    vec4 vec = vec4();
    vec.x = x;
    vec.y = y;
    vec.z = z;
    vec.w = w;

    return vec;
}








class vec3 {
public:
    float x, y, z;
    static vec3 create(float x, float y, float z);
    static vec3 normalize(vec3 a);
    static vec3 cross(vec3 a, vec3 b);

    vec3 operator+(const vec3 a) {
        return vec3::create(a.x + x, a.y + y, a.z + z);
    }
    vec3 operator-(const vec3 a) {
        return vec3::create(x - a.x, y - a.y, z - a.z);
    }
};

vec3 vec3::create(float x, float y, float z) {
    vec3 vec = vec3();
    vec.x = x;
    vec.y = y;
    vec.z = z;

    return vec;
}
vec3 vec3::normalize(vec3 a) {
    float magnitude = sqrt((a.x * a.x) + (a.y * a.y) + (a.z * a.z));
    return vec3::create(a.x / magnitude, a.y / magnitude, a.z / magnitude);
}
vec3 vec3::cross(vec3 a, vec3 b) {
    return vec3::create(
      a.y*b.z - a.z*b.y,
      a.z*b.x - a.x*b.z, 
      a.x*b.y - a.y*b.x);
}









class matrix4 {
public:
    vec4 row1, row2, row3, row4;

    static matrix4 create(vec4 row1, vec4 row2, vec4 row3, vec4 row4);
    static matrix4 mult(matrix4 a, matrix4 b);
    static vec4    mult(matrix4 a, vec4 b);
};

matrix4 matrix4::create(vec4 row1, vec4 row2, vec4 row3, vec4 row4) {
    matrix4 matr = matrix4();
    matr.row1 = row1;
    matr.row2 = row2;
    matr.row3 = row3;
    matr.row4 = row4;
    return matr;
}
matrix4 matrix4::mult(matrix4 a, matrix4 b) {

    vec4 row1 = vec4::create(
      a.row1.x * b.row1.x + a.row1.y * b.row2.x + a.row1.z * b.row3.x + a.row1.w * b.row4.x, 
      a.row1.x * b.row1.y + a.row1.y * b.row2.y + a.row1.z * b.row3.y + a.row1.w * b.row4.y, 
      a.row1.x * b.row1.z + a.row1.y * b.row2.x + a.row1.z * b.row3.z + a.row1.w * b.row4.z, 
      a.row1.x * b.row1.w + a.row1.y * b.row2.w + a.row1.z * b.row3.w + a.row1.w * b.row4.w);

    vec4 row2 = vec4::create(
      a.row2.x * b.row1.x + a.row2.y * b.row2.x + a.row2.z * b.row3.x + a.row2.w * b.row4.x, 
      a.row2.x * b.row1.y + a.row2.y * b.row2.y + a.row2.z * b.row3.y + a.row2.w * b.row4.y, 
      a.row2.x * b.row1.z + a.row2.y * b.row2.x + a.row2.z * b.row3.z + a.row2.w * b.row4.z, 
      a.row2.x * b.row1.w + a.row2.y * b.row2.w + a.row2.z * b.row3.w + a.row2.w * b.row4.w);

    vec4 row3 = vec4::create(
      a.row3.x * b.row1.x + a.row3.y * b.row2.x + a.row3.z * b.row3.x + a.row3.w * b.row4.x, 
      a.row3.x * b.row1.y + a.row3.y * b.row2.y + a.row3.z * b.row3.y + a.row3.w * b.row4.y, 
      a.row3.x * b.row1.z + a.row3.y * b.row2.x + a.row3.z * b.row3.z + a.row3.w * b.row4.z, 
      a.row3.x * b.row1.w + a.row3.y * b.row2.w + a.row3.z * b.row3.w + a.row3.w * b.row4.w);

    vec4 row4 = vec4::create(
      a.row4.x * b.row1.x + a.row4.y * b.row2.x + a.row4.z * b.row3.x + a.row4.w * b.row4.x, 
      a.row4.x * b.row1.y + a.row4.y * b.row2.y + a.row4.z * b.row3.y + a.row4.w * b.row4.y, 
      a.row4.x * b.row1.z + a.row4.y * b.row2.x + a.row4.z * b.row3.z + a.row4.w * b.row4.z, 
      a.row4.x * b.row1.w + a.row4.y * b.row2.w + a.row4.z * b.row3.w + a.row4.w * b.row4.w);

    return matrix4::create(row1, row2, row3, row4);
}
vec4 matrix4::mult(matrix4 a, vec4 b) {
    float x = a.row1.x * b.x + a.row1.y * b.y + a.row1.z * b.z + a.row1.w * b.w;
    float y = a.row2.x * b.x + a.row2.y * b.y + a.row2.z * b.z + a.row2.w * b.w;
    float z = a.row3.x * b.x + a.row3.y * b.y + a.row3.z * b.z + a.row3.w * b.w;
    float w = a.row4.x * b.x + a.row4.y * b.y + a.row4.z * b.z + a.row4.w * b.w;

    return vec4::create(x, y, z, w);
}



matrix4 perspective(float aspect, float fovDeg, float far, float near) {

    float DegToRad = (fovDeg/180) * 3.14159265358979;

    vec4 row1 = vec4::create(1/(aspect * tan(DegToRad)), 0,                     0,                         0);
    vec4 row2 = vec4::create(0,                          1/(tan(DegToRad/2)),   0,                         0);
    vec4 row3 = vec4::create(0,                          0,                    -(far + near)/(far - near), -(2 * far * near)/(far - near));
    vec4 row4 = vec4::create(0,                          0,                    -1,                         0);

    return matrix4::create(row1, row2, row3, row4);
}
matrix4 lookat(vec3 eye, vec3 target, vec3 up) {

    vec3 z = vec3::normalize(target - eye);
    vec3 x = vec3::normalize(vec3::cross(up, z));
    vec3 y = vec3::normalize(vec3::cross(z,  x));

    float t1 = -((x.x * eye.x) + (x.y * eye.y) + (x.z * eye.z));
    float t2 = -((y.x * eye.x) + (y.y * eye.y) + (y.z * eye.z));
    float t3 = -((z.x * eye.x) + (z.y * eye.y) + (z.z * eye.z));

    vec4 row1 = vec4::create(x.x, x.y, x.z, 0);
    vec4 row2 = vec4::create(y.x, y.y, y.z, 0);
    vec4 row3 = vec4::create(z.x, z.y, z.z, 0);
    vec4 row4 = vec4::create(t1,  t2,  t3,  1);

    return matrix4::create(row1, row2, row3, row4);
}

matrix4 projection = perspective(1.f, 45.f, 1000.1f, 1.f);
matrix4 position = lookat(vec3::create(0, 0, -2), vec3::create(0, 0, 0), vec3::create(0, 1, 0));



vec3 t1 = vec3::create(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, 0);
vec3 t2 = vec3::create(SCREEN_WIDTH/2 + 50, SCREEN_HEIGHT/2 - 50, 0);
vec3 t3 = vec3::create(SCREEN_WIDTH/2 - 50, SCREEN_HEIGHT/2 - 50, 0);



vec3 toScreenSpace(vec4 coordinate) {
    float x = ((coordinate.x + 1)/2.f) * SCREEN_WIDTH;
    float y = ((coordinate.y + 1)/2.f) * SCREEN_HEIGHT;

    return vec3::create(coordinate.x, coordinate.y, 0);
}



void setup() {
    displ.begin();
    displ.fillScreen(HEX_COLOR_BLACK);
}

void loop() {
    angle += 0.1f;

    position = lookat(vec3::create(100 * sin(angle), 10, 100 * cos(angle)), vec3::create(0, 0, 0), vec3::create(0, 1, 0));

    int16_t radius = 50;
    int16_t x_point1 = radius * cos(angle);
    int16_t y_point1 = radius * sin(angle);

    int16_t x_point2 = -x_point1;
    int16_t y_point2 = -y_point1;

    displ.fillScreen(HEX_COLOR_BLACK);

    vec3 translatedTriangle1 = toScreenSpace(matrix4::mult(matrix4::mult(projection, position), vec4::create(t1.x, t1.y, t1.z, 1)));
    vec3 translatedTriangle2 = toScreenSpace(matrix4::mult(matrix4::mult(projection, position), vec4::create(t2.x, t2.y, t2.z, 1)));
    vec3 translatedTriangle3 = toScreenSpace(matrix4::mult(matrix4::mult(projection, position), vec4::create(t3.x, t3.y, t3.z, 1)));

    displ.drawLine(translatedTriangle1.x, translatedTriangle1.y, translatedTriangle2.x, translatedTriangle2.y, HEX_COLOR_RED);
    displ.drawLine(translatedTriangle3.x, translatedTriangle3.y, translatedTriangle2.x, translatedTriangle2.y, HEX_COLOR_GREEN);
    displ.drawLine(translatedTriangle3.x, translatedTriangle3.y, translatedTriangle1.x, translatedTriangle1.y, HEX_COLOR_BLUE);
}
