#pragma once

struct Vector2 {
    int x;
    int y;
};

struct Vector3 {
    double x;
    double y;
    double z;

    Vector3 operator*(const Vector3& other) const;
    Vector3 operator-(const Vector3& other) const;
    void operator=(const Vector3& other) {
        x = other.x;
        y = other.y;
        z = other.z;
    }
};

struct Matrix3x3 {
    Matrix3x3(double a, double b, double c, double d, double e, double f, double g, double h, double i) {
        m[0] = a;
        m[1] = b;
        m[2] = c;
        m[3] = d;
        m[4] = e;
        m[5] = f;
        m[6] = g;
        m[7] = h;
        m[8] = i;
    }

    Matrix3x3(const Matrix3x3& is) {
        for (int i = 0; i < 9; ++i) {
            m[i] = is.m[i];
        }
    };

    Matrix3x3() = default;

    double m[9];

    bool operator==(const Matrix3x3& other) const;

    Matrix3x3 operator*(const Matrix3x3& other) const;
    Vector3 operator*(const Vector3& other) const;

    double operator[](int index) const;

    double& operator[](int index);

    void operator=(const Matrix3x3& other) {
        for (int i = 0; i < 9; ++i) {
            m[i] = other.m[i];
        }
    }
};

int abs(int x);
int pow(int x);
int dot(Vector3 a, Vector3 b);
double sqrt(int x);