#ifndef MATRIX4F_H
#define MATRIX4F_H

class Matrix4f
{
private:
	static const int MATRIX_SIZE = 16;
public:
	static const int M00 = 0, M01 = 1, M02 = 2, M03 = 3,
					 M10 = 4, M11 = 5, M12 = 6, M13 = 7,
					 M20 = 8, M21 = 9, M22 = 10, M23 = 11,
					 M30 = 12, M31 = 13, M32 = 14, M33 = 15;
	float values[MATRIX_SIZE];

	Matrix4f()
	{
		this->setToIdentity();
	}

	Matrix4f(float values[])
	{
		this->set(values);
	}

	Matrix4f(Matrix4f &other)
	{
		this->set(other);
	}

	Matrix4f(float m00, float m01, float m02, float m03,
             float m10, float m11, float m12, float m13,
             float m20, float m21, float m22, float m23,
             float m30, float m31, float m32, float m33)
	{
		this->set(m00, m01, m02, m03, m10, m11, m12, m13, m20, m21, m22, m23, m30, m31, m32, m33);
	}

	~Matrix4f()
	{
	}

	Matrix4f *setToIdentity()
	{
		this->values[M00] = 1;
        this->values[M01] = 0;
        this->values[M02] = 0;
        this->values[M03] = 0;

        this->values[M10] = 0;
        this->values[M11] = 1;
        this->values[M12] = 0;
        this->values[M13] = 0;

        this->values[M20] = 0;
        this->values[M21] = 0;
        this->values[M22] = 1;
        this->values[M23] = 0;

        this->values[M30] = 0;
        this->values[M31] = 0;
        this->values[M32] = 0;
        this->values[M33] = 1;

        return this;
	}

	Matrix4f *set(Matrix4f &other)
	{
		for (int i = 0; i < MATRIX_SIZE; i++)
		{
			this->values[i] = other.values[i];
		}
		return this;
	}

	Matrix4f *set(float m00, float m01, float m02, float m03,
             float m10, float m11, float m12, float m13,
             float m20, float m21, float m22, float m23,
             float m30, float m31, float m32, float m33)
	{
		 this->values[M00] = m00;
         this->values[M01] = m01;
         this->values[M02] = m02;
         this->values[M03] = m03;

         this->values[M10] = m10;
         this->values[M11] = m11;
         this->values[M12] = m12;
         this->values[M13] = m13;

         this->values[M20] = m20;
         this->values[M21] = m21;
         this->values[M22] = m22;
         this->values[M23] = m23;

         this->values[M30] = m30;
         this->values[M31] = m31;
         this->values[M32] = m32;
         this->values[M33] = m33;

         return this;
	}

	Matrix4f *set(float values[])
	{
		for (int i = 0; i < MATRIX_SIZE; i++)
		{
			this->values[i] = values[i];
		}
		return this;
	}

	Matrix4f *mult(Matrix4f &other)
	{ 
		Matrix4f *res = new Matrix4f();

		float _M00 = this->values[M00] * other.values[M00] + this->values[M10] * other.values[M01] + this->values[M20] * other.values[M02] + this->values[M30] * other.values[M03];
		float _M01 = this->values[M01] * other.values[M00] + this->values[M11] * other.values[M01] + this->values[M21] * other.values[M02] + this->values[M31] * other.values[M03];
		float _M02 = this->values[M02] * other.values[M00] + this->values[M12] * other.values[M01] + this->values[M22] * other.values[M02] + this->values[M32] * other.values[M03];
		float _M03 = this->values[M03] * other.values[M00] + this->values[M13] * other.values[M01] + this->values[M23] * other.values[M02] + this->values[M33] * other.values[M03];
		float _M10 = this->values[M00] * other.values[M10] + this->values[M10] * other.values[M11] + this->values[M20] * other.values[M12] + this->values[M30] * other.values[M13];
		float _M11 = this->values[M01] * other.values[M10] + this->values[M11] * other.values[M11] + this->values[M21] * other.values[M12] + this->values[M31] * other.values[M13];
		float _M12 = this->values[M02] * other.values[M10] + this->values[M12] * other.values[M11] + this->values[M22] * other.values[M12] + this->values[M32] * other.values[M13];
		float _M13 = this->values[M03] * other.values[M10] + this->values[M13] * other.values[M11] + this->values[M23] * other.values[M12] + this->values[M33] * other.values[M13];
		float _M20 = this->values[M00] * other.values[M20] + this->values[M10] * other.values[M21] + this->values[M20] * other.values[M22] + this->values[M30] * other.values[M23];
		float _M21 = this->values[M01] * other.values[M20] + this->values[M11] * other.values[M21] + this->values[M21] * other.values[M22] + this->values[M31] * other.values[M23];
		float _M22 = this->values[M02] * other.values[M20] + this->values[M12] * other.values[M21] + this->values[M22] * other.values[M22] + this->values[M32] * other.values[M23];
		float _M23 = this->values[M03] * other.values[M20] + this->values[M13] * other.values[M21] + this->values[M23] * other.values[M22] + this->values[M33] * other.values[M23];
		float _M30 = this->values[M00] * other.values[M30] + this->values[M10] * other.values[M31] + this->values[M20] * other.values[M32] + this->values[M30] * other.values[M33];
		float _M31 = this->values[M01] * other.values[M30] + this->values[M11] * other.values[M31] + this->values[M21] * other.values[M32] + this->values[M31] * other.values[M33];
		float _M32 = this->values[M02] * other.values[M30] + this->values[M12] * other.values[M31] + this->values[M22] * other.values[M32] + this->values[M32] * other.values[M33];
		float _M33 = this->values[M03] * other.values[M30] + this->values[M13] * other.values[M31] + this->values[M23] * other.values[M32] + this->values[M33] * other.values[M33];

		res->values[M00] = _M00;
		res->values[M01] = _M01;
		res->values[M02] = _M02;
		res->values[M03] = _M03;

		res->values[M10] = _M10;
		res->values[M11] = _M11;
		res->values[M12] = _M12;
		res->values[M13] = _M13;

		res->values[M20] = _M20;
		res->values[M21] = _M21;
		res->values[M22] = _M22;
		res->values[M23] = _M23;

		res->values[M30] = _M30;
		res->values[M31] = _M31;
		res->values[M32] = _M32;
		res->values[M33] = _M33;

		return res;
	}

	Matrix4f *multStore(Matrix4f &other)
	{

		float _M00 = this->values[M00] * other.values[M00] + this->values[M10] * other.values[M01] + this->values[M20] * other.values[M02] + this->values[M30] * other.values[M03];
		float _M01 = this->values[M01] * other.values[M00] + this->values[M11] * other.values[M01] + this->values[M21] * other.values[M02] + this->values[M31] * other.values[M03];
		float _M02 = this->values[M02] * other.values[M00] + this->values[M12] * other.values[M01] + this->values[M22] * other.values[M02] + this->values[M32] * other.values[M03];
		float _M03 = this->values[M03] * other.values[M00] + this->values[M13] * other.values[M01] + this->values[M23] * other.values[M02] + this->values[M33] * other.values[M03];
		float _M10 = this->values[M00] * other.values[M10] + this->values[M10] * other.values[M11] + this->values[M20] * other.values[M12] + this->values[M30] * other.values[M13];
		float _M11 = this->values[M01] * other.values[M10] + this->values[M11] * other.values[M11] + this->values[M21] * other.values[M12] + this->values[M31] * other.values[M13];
		float _M12 = this->values[M02] * other.values[M10] + this->values[M12] * other.values[M11] + this->values[M22] * other.values[M12] + this->values[M32] * other.values[M13];
		float _M13 = this->values[M03] * other.values[M10] + this->values[M13] * other.values[M11] + this->values[M23] * other.values[M12] + this->values[M33] * other.values[M13];
		float _M20 = this->values[M00] * other.values[M20] + this->values[M10] * other.values[M21] + this->values[M20] * other.values[M22] + this->values[M30] * other.values[M23];
		float _M21 = this->values[M01] * other.values[M20] + this->values[M11] * other.values[M21] + this->values[M21] * other.values[M22] + this->values[M31] * other.values[M23];
		float _M22 = this->values[M02] * other.values[M20] + this->values[M12] * other.values[M21] + this->values[M22] * other.values[M22] + this->values[M32] * other.values[M23];
		float _M23 = this->values[M03] * other.values[M20] + this->values[M13] * other.values[M21] + this->values[M23] * other.values[M22] + this->values[M33] * other.values[M23];
		float _M30 = this->values[M00] * other.values[M30] + this->values[M10] * other.values[M31] + this->values[M20] * other.values[M32] + this->values[M30] * other.values[M33];
		float _M31 = this->values[M01] * other.values[M30] + this->values[M11] * other.values[M31] + this->values[M21] * other.values[M32] + this->values[M31] * other.values[M33];
		float _M32 = this->values[M02] * other.values[M30] + this->values[M12] * other.values[M31] + this->values[M22] * other.values[M32] + this->values[M32] * other.values[M33];
		float _M33 = this->values[M03] * other.values[M30] + this->values[M13] * other.values[M31] + this->values[M23] * other.values[M32] + this->values[M33] * other.values[M33];

		this->values[M00] = _M00;
		this->values[M01] = _M01;
		this->values[M02] = _M02;
		this->values[M03] = _M03;

		this->values[M10] = _M10;
		this->values[M11] = _M11;
		this->values[M12] = _M12;
		this->values[M13] = _M13;

		this->values[M20] = _M20;
		this->values[M21] = _M21;
		this->values[M22] = _M22;
		this->values[M23] = _M23;

		this->values[M30] = _M30;
		this->values[M31] = _M31;
		this->values[M32] = _M32;
		this->values[M33] = _M33;

		return this;
	}

	Matrix4f *mult(float scalar)
	{
		Matrix4f *res = new Matrix4f();
		for (int i = 0; i < MATRIX_SIZE; i++)
		{
			res->values[i] = this->values[i] * scalar;
		}
		return res;
	}

	Matrix4f *multStore(float scalar)
	{
		for (int i = 0; i < MATRIX_SIZE; i++)
		{
			this->values[i] = this->values[i] * scalar;
		}
		return this;
	}

	Matrix4f *transpose()
	{
		Matrix4f *res = new Matrix4f();
		
		res->values[M00] = this->values[M00];
        res->values[M01] = this->values[M10];
        res->values[M02] = this->values[M20];
        res->values[M03] = this->values[M30];

        res->values[M10] = this->values[M01];
        res->values[M11] = this->values[M11];
        res->values[M12] = this->values[M21];
        res->values[M13] = this->values[M31];

        res->values[M20] = this->values[M02];
        res->values[M21] = this->values[M12];
        res->values[M22] = this->values[M22];
        res->values[M23] = this->values[M32];

        res->values[M30] = this->values[M03];
        res->values[M31] = this->values[M13];
        res->values[M32] = this->values[M23];
        res->values[M33] = this->values[M33];

		return res;
	}

	Matrix4f *transposeStore()
	{
		Matrix4f tmp;
		
		tmp.values[M00] = this->values[M00];
        tmp.values[M01] = this->values[M10];
        tmp.values[M02] = this->values[M20];
        tmp.values[M03] = this->values[M30];

        tmp.values[M10] = this->values[M01];
        tmp.values[M11] = this->values[M11];
        tmp.values[M12] = this->values[M21];
        tmp.values[M13] = this->values[M31];

        tmp.values[M20] = this->values[M02];
        tmp.values[M21] = this->values[M12];
        tmp.values[M22] = this->values[M22];
        tmp.values[M23] = this->values[M32];

        tmp.values[M30] = this->values[M03];
        tmp.values[M31] = this->values[M13];
        tmp.values[M32] = this->values[M23];
        tmp.values[M33] = this->values[M33];

		this->set(tmp);

		return this;
	}

	Matrix4f *invert()
	{
		Matrix4f *res = new Matrix4f(*this);
		return res->invertStore();
	}

	Matrix4f *invertStore()
	{
		float tmp[16];
		float l_det = this->values[M30] * this->values[M21] * this->values[M12] * this->values[M03] - this->values[M20] * this->values[M31] * this->values[M12] * this->values[M03] - this->values[M30] * this->values[M11]
            * this->values[M22] * this->values[M03] + this->values[M10] * this->values[M31] * this->values[M22] * this->values[M03] + this->values[M20] * this->values[M11] * this->values[M32] * this->values[M03] - this->values[M10]
            * this->values[M21] * this->values[M32] * this->values[M03] - this->values[M30] * this->values[M21] * this->values[M02] * this->values[M13] + this->values[M20] * this->values[M31] * this->values[M02] * this->values[M13]
            + this->values[M30] * this->values[M01] * this->values[M22] * this->values[M13] - this->values[M00] * this->values[M31] * this->values[M22] * this->values[M13] - this->values[M20] * this->values[M01] * this->values[M32]
            * this->values[M13] + this->values[M00] * this->values[M21] * this->values[M32] * this->values[M13] + this->values[M30] * this->values[M11] * this->values[M02] * this->values[M23] - this->values[M10] * this->values[M31]
            * this->values[M02] * this->values[M23] - this->values[M30] * this->values[M01] * this->values[M12] * this->values[M23] + this->values[M00] * this->values[M31] * this->values[M12] * this->values[M23] + this->values[M10]
            * this->values[M01] * this->values[M32] * this->values[M23] - this->values[M00] * this->values[M11] * this->values[M32] * this->values[M23] - this->values[M20] * this->values[M11] * this->values[M02] * this->values[M33]
            + this->values[M10] * this->values[M21] * this->values[M02] * this->values[M33] + this->values[M20] * this->values[M01] * this->values[M12] * this->values[M33] - this->values[M00] * this->values[M21] * this->values[M12]
            * this->values[M33] - this->values[M10] * this->values[M01] * this->values[M22] * this->values[M33] + this->values[M00] * this->values[M11] * this->values[M22] * this->values[M33];

		if (l_det == 0) return this;

        float inv_det = 1.0f / l_det;

		tmp[M00] = this->values[M12] * this->values[M23] * this->values[M31] - this->values[M13] * this->values[M22] * this->values[M31] + this->values[M13] * this->values[M21] * this->values[M32] - this->values[M11]
                * this->values[M23] * this->values[M32] - this->values[M12] * this->values[M21] * this->values[M33] + this->values[M11] * this->values[M22] * this->values[M33];
            tmp[M01] = this->values[M03] * this->values[M22] * this->values[M31] - this->values[M02] * this->values[M23] * this->values[M31] - this->values[M03] * this->values[M21] * this->values[M32] + this->values[M01]
                * this->values[M23] * this->values[M32] + this->values[M02] * this->values[M21] * this->values[M33] - this->values[M01] * this->values[M22] * this->values[M33];
            tmp[M02] = this->values[M02] * this->values[M13] * this->values[M31] - this->values[M03] * this->values[M12] * this->values[M31] + this->values[M03] * this->values[M11] * this->values[M32] - this->values[M01]
                * this->values[M13] * this->values[M32] - this->values[M02] * this->values[M11] * this->values[M33] + this->values[M01] * this->values[M12] * this->values[M33];
            tmp[M03] = this->values[M03] * this->values[M12] * this->values[M21] - this->values[M02] * this->values[M13] * this->values[M21] - this->values[M03] * this->values[M11] * this->values[M22] + this->values[M01]
                * this->values[M13] * this->values[M22] + this->values[M02] * this->values[M11] * this->values[M23] - this->values[M01] * this->values[M12] * this->values[M23];
            tmp[M10] = this->values[M13] * this->values[M22] * this->values[M30] - this->values[M12] * this->values[M23] * this->values[M30] - this->values[M13] * this->values[M20] * this->values[M32] + this->values[M10]
                * this->values[M23] * this->values[M32] + this->values[M12] * this->values[M20] * this->values[M33] - this->values[M10] * this->values[M22] * this->values[M33];
            tmp[M11] = this->values[M02] * this->values[M23] * this->values[M30] - this->values[M03] * this->values[M22] * this->values[M30] + this->values[M03] * this->values[M20] * this->values[M32] - this->values[M00]
                * this->values[M23] * this->values[M32] - this->values[M02] * this->values[M20] * this->values[M33] + this->values[M00] * this->values[M22] * this->values[M33];
            tmp[M12] = this->values[M03] * this->values[M12] * this->values[M30] - this->values[M02] * this->values[M13] * this->values[M30] - this->values[M03] * this->values[M10] * this->values[M32] + this->values[M00]
                * this->values[M13] * this->values[M32] + this->values[M02] * this->values[M10] * this->values[M33] - this->values[M00] * this->values[M12] * this->values[M33];
            tmp[M13] = this->values[M02] * this->values[M13] * this->values[M20] - this->values[M03] * this->values[M12] * this->values[M20] + this->values[M03] * this->values[M10] * this->values[M22] - this->values[M00]
                * this->values[M13] * this->values[M22] - this->values[M02] * this->values[M10] * this->values[M23] + this->values[M00] * this->values[M12] * this->values[M23];
            tmp[M20] = this->values[M11] * this->values[M23] * this->values[M30] - this->values[M13] * this->values[M21] * this->values[M30] + this->values[M13] * this->values[M20] * this->values[M31] - this->values[M10]
                * this->values[M23] * this->values[M31] - this->values[M11] * this->values[M20] * this->values[M33] + this->values[M10] * this->values[M21] * this->values[M33];
            tmp[M21] = this->values[M03] * this->values[M21] * this->values[M30] - this->values[M01] * this->values[M23] * this->values[M30] - this->values[M03] * this->values[M20] * this->values[M31] + this->values[M00]
                * this->values[M23] * this->values[M31] + this->values[M01] * this->values[M20] * this->values[M33] - this->values[M00] * this->values[M21] * this->values[M33];
            tmp[M22] = this->values[M01] * this->values[M13] * this->values[M30] - this->values[M03] * this->values[M11] * this->values[M30] + this->values[M03] * this->values[M10] * this->values[M31] - this->values[M00]
                * this->values[M13] * this->values[M31] - this->values[M01] * this->values[M10] * this->values[M33] + this->values[M00] * this->values[M11] * this->values[M33];
            tmp[M23] = this->values[M03] * this->values[M11] * this->values[M20] - this->values[M01] * this->values[M13] * this->values[M20] - this->values[M03] * this->values[M10] * this->values[M21] + this->values[M00]
                * this->values[M13] * this->values[M21] + this->values[M01] * this->values[M10] * this->values[M23] - this->values[M00] * this->values[M11] * this->values[M23];
            tmp[M30] = this->values[M12] * this->values[M21] * this->values[M30] - this->values[M11] * this->values[M22] * this->values[M30] - this->values[M12] * this->values[M20] * this->values[M31] + this->values[M10]
                * this->values[M22] * this->values[M31] + this->values[M11] * this->values[M20] * this->values[M32] - this->values[M10] * this->values[M21] * this->values[M32];
            tmp[M31] = this->values[M01] * this->values[M22] * this->values[M30] - this->values[M02] * this->values[M21] * this->values[M30] + this->values[M02] * this->values[M20] * this->values[M31] - this->values[M00]
                * this->values[M22] * this->values[M31] - this->values[M01] * this->values[M20] * this->values[M32] + this->values[M00] * this->values[M21] * this->values[M32];
            tmp[M32] = this->values[M02] * this->values[M11] * this->values[M30] - this->values[M01] * this->values[M12] * this->values[M30] - this->values[M02] * this->values[M10] * this->values[M31] + this->values[M00]
                * this->values[M12] * this->values[M31] + this->values[M01] * this->values[M10] * this->values[M32] - this->values[M00] * this->values[M11] * this->values[M32];
            tmp[M33] = this->values[M01] * this->values[M12] * this->values[M20] - this->values[M02] * this->values[M11] * this->values[M20] + this->values[M02] * this->values[M10] * this->values[M21] - this->values[M00]
                * this->values[M12] * this->values[M21] - this->values[M01] * this->values[M10] * this->values[M22] + this->values[M00] * this->values[M11] * this->values[M22];
        
		this->values[M00] = tmp[M00] * inv_det;
        this->values[M01] = tmp[M01] * inv_det;
        this->values[M02] = tmp[M02] * inv_det;
        this->values[M03] = tmp[M03] * inv_det;
        this->values[M10] = tmp[M10] * inv_det;
        this->values[M11] = tmp[M11] * inv_det;
        this->values[M12] = tmp[M12] * inv_det;
        this->values[M13] = tmp[M13] * inv_det;
        this->values[M20] = tmp[M20] * inv_det;
        this->values[M21] = tmp[M21] * inv_det;
        this->values[M22] = tmp[M22] * inv_det;
        this->values[M23] = tmp[M23] * inv_det;
        this->values[M30] = tmp[M30] * inv_det;
        this->values[M31] = tmp[M31] * inv_det;
        this->values[M32] = tmp[M32] * inv_det;
        this->values[M33] = tmp[M33] * inv_det;

		return this;
	}
};
#endif