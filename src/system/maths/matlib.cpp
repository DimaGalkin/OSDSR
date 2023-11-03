#include "matlib.hpp"

int abs(int x) {
    return x < 0 ? -x : x;
}

int pow(int x) {
    return x * x;
}

Matrix3x3 Matrix3x3::operator*(const Matrix3x3& other) const {
    Matrix3x3 result;

    result.m[0] = m[0] * other.m[0] + m[1] * other.m[3] + m[2] * other.m[6];
    result.m[1] = m[0] * other.m[1] + m[1] * other.m[4] + m[2] * other.m[7];
    result.m[2] = m[0] * other.m[2] + m[1] * other.m[5] + m[2] * other.m[8];

    result.m[3] = m[3] * other.m[0] + m[4] * other.m[3] + m[5] * other.m[6];
    result.m[4] = m[3] * other.m[1] + m[4] * other.m[4] + m[5] * other.m[7];
    result.m[5] = m[3] * other.m[2] + m[4] * other.m[5] + m[5] * other.m[8];

    result.m[6] = m[6] * other.m[0] + m[7] * other.m[3] + m[8] * other.m[6];
    result.m[7] = m[6] * other.m[1] + m[7] * other.m[4] + m[8] * other.m[7];
    result.m[8] = m[6] * other.m[2] + m[7] * other.m[5] + m[8] * other.m[8];

    return result;
}

bool Matrix3x3::operator==(const Matrix3x3& other) const {
    return m[0] == other.m[0] && m[1] == other.m[1] && m[2] == other.m[2] &&
           m[3] == other.m[3] && m[4] == other.m[4] && m[5] == other.m[5] &&
           m[6] == other.m[6] && m[7] == other.m[7] && m[8] == other.m[8];
}

double Matrix3x3::operator[](int index) const {
    return m[index];
}

double& Matrix3x3::operator[](int index) {
    return m[index];
}

Vector3 Matrix3x3::operator*(const Vector3& other) const {
    Vector3 result;

    result.x = m[0] * other.x + m[1] * other.y + m[2] * other.z;
    result.y = m[3] * other.x + m[4] * other.y + m[5] * other.z;
    result.z = m[6] * other.x + m[7] * other.y + m[8] * other.z;

    return result;
}

int dot(Vector3 a, Vector3 b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

Vector3 Vector3::operator*(const Vector3& other) const {
    Vector3 result;

    result.x = x * other.x;
    result.y = y * other.y;
    result.z = z * other.z;

    return result;
}

double sqrt(int x) {
    double result = 0;
    double last_result = 0;

    while (true) {
        result = (result + x / result) / 2;

        if (result == last_result) break;

        last_result = result;
    }

    return result;
}

Vector3 Vector3::operator-(const Vector3& other) const {
    Vector3 result;

    result.x = x - other.x;
    result.y = y - other.y;
    result.z = z - other.z;

    return result;
}