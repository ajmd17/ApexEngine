#ifndef MATRIX4F_H
#define MATRIX4F_H

#include <iostream>
using std::ostream;

namespace apex
{
	class Matrix4f
	{
	private:
		static const int MATRIX_SIZE = 16;

		float _1dArray[16];
	public:
		/*static const int M00 = 0, M01 = 1, M02 = 2, M03 = 3,
						 M10 = 4, M11 = 5, M12 = 6, M13 = 7,
						 M20 = 8, M21 = 9, M22 = 10, M23 = 11,
						 M30 = 12, M31 = 13, M32 = 14, M33 = 15;*/

		float values[4][4];

		Matrix4f()
		{
			setToIdentity();
		}

		Matrix4f(float values[][4])
		{
			set(values);
		}

		Matrix4f(Matrix4f &other)
		{
			set(other);
		}

		Matrix4f(float m00, float m01, float m02, float m03,
			float m10, float m11, float m12, float m13,
			float m20, float m21, float m22, float m23,
			float m30, float m31, float m32, float m33)
		{
			set(m00, m01, m02, m03,
				m10, m11, m12, m13,
				m20, m21, m22, m23,
				m30, m31, m32, m33);
		}

		~Matrix4f()
		{
		}

		float *get1DArray()
		{
			// update 1D array before returning
			int idx = 0;
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					idx = i * 4 + j;
					_1dArray[idx] = values[i][j];
				}
			}
			return _1dArray;
		}

		template <int i, int j>
		float getM() const
		{
			return values[i][j];
		}

		template <int i, int j>
		void setM(float value)
		{
			values[i][j] = value;
		}

		Matrix4f &setToIdentity()
		{
			values[0][0] = 1;
			values[0][1] = 0;
			values[0][2] = 0;
			values[0][3] = 0;

			values[1][0] = 0;
			values[1][1] = 1;
			values[1][2] = 0;
			values[1][3] = 0;

			values[2][0] = 0;
			values[2][1] = 0;
			values[2][2] = 1;
			values[2][3] = 0;

			values[3][0] = 0;
			values[3][1] = 0;
			values[3][2] = 0;
			values[3][3] = 1;

			return *this;
		}

		Matrix4f &set(Matrix4f &other)
		{
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					this->values[i][j] = other.values[i][j];
				}
			}
			return *this;
		}

		Matrix4f &set(float m00, float m01, float m02, float m03,
			float m10, float m11, float m12, float m13,
			float m20, float m21, float m22, float m23,
			float m30, float m31, float m32, float m33)
		{
			values[0][0] = m00;
			values[0][1] = m01;
			values[0][2] = m02;
			values[0][2] = m03;

			values[1][0] = m10;
			values[1][1] = m11;
			values[1][2] = m12;
			values[1][3] = m13;

			values[2][0] = m20;
			values[2][1] = m21;
			values[2][2] = m22;
			values[2][3] = m23;

			values[3][0] = m30;
			values[3][1] = m31;
			values[3][2] = m32;
			values[3][3] = m33;

			return *this;
		}

		Matrix4f &set(float values[][4])
		{
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					this->values[i][j] = values[i][j];
				}
			}
			return *this;
		}

		Matrix4f &multiply(Matrix4f &other)
		{

			float _M00 = values[0][0] * other.values[0][0] + values[1][0] * other.values[0][1] + values[2][0] * other.values[0][2] + values[3][0] * other.values[0][3];
			float _M01 = values[0][1] * other.values[0][0] + values[1][1] * other.values[0][1] + values[2][1] * other.values[0][2] + values[3][1] * other.values[0][3];
			float _M02 = values[0][2] * other.values[0][0] + values[1][2] * other.values[0][1] + values[2][2] * other.values[0][2] + values[3][2] * other.values[0][3];
			float _M03 = values[0][3] * other.values[0][0] + values[1][3] * other.values[0][1] + values[2][3] * other.values[0][2] + values[3][3] * other.values[0][3];
			float _M10 = values[0][0] * other.values[1][0] + values[1][0] * other.values[1][1] + values[2][0] * other.values[1][2] + values[3][0] * other.values[1][3];
			float _M11 = values[0][1] * other.values[1][0] + values[1][1] * other.values[1][1] + values[2][1] * other.values[1][2] + values[3][1] * other.values[1][3];
			float _M12 = values[0][2] * other.values[1][0] + values[1][2] * other.values[1][1] + values[2][2] * other.values[1][2] + values[3][2] * other.values[1][3];
			float _M13 = values[0][3] * other.values[1][0] + values[1][3] * other.values[1][1] + values[2][3] * other.values[1][2] + values[3][3] * other.values[1][3];
			float _M20 = values[0][0] * other.values[2][0] + values[1][0] * other.values[2][1] + values[2][0] * other.values[2][2] + values[3][0] * other.values[2][3];
			float _M21 = values[0][1] * other.values[2][0] + values[1][1] * other.values[2][1] + values[2][1] * other.values[2][2] + values[3][1] * other.values[2][3];
			float _M22 = values[0][2] * other.values[2][0] + values[1][2] * other.values[2][1] + values[2][2] * other.values[2][2] + values[3][2] * other.values[2][3];
			float _M23 = values[0][3] * other.values[2][0] + values[1][3] * other.values[2][1] + values[2][3] * other.values[2][2] + values[3][3] * other.values[2][3];
			float _M30 = values[0][0] * other.values[3][0] + values[1][0] * other.values[3][1] + values[2][0] * other.values[3][2] + values[3][0] * other.values[3][3];
			float _M31 = values[0][1] * other.values[3][0] + values[1][1] * other.values[3][1] + values[2][1] * other.values[3][2] + values[3][1] * other.values[3][3];
			float _M32 = values[0][2] * other.values[3][0] + values[1][2] * other.values[3][1] + values[2][2] * other.values[3][2] + values[3][2] * other.values[3][3];
			float _M33 = values[0][3] * other.values[3][0] + values[1][3] * other.values[3][1] + values[2][3] * other.values[3][2] + values[3][3] * other.values[3][3];

			values[0][0] = _M00;
			values[0][1] = _M01;
			values[0][2] = _M02;
			values[0][3] = _M03;

			values[1][0] = _M10;
			values[1][1] = _M11;
			values[1][2] = _M12;
			values[1][3] = _M13;

			values[2][0] = _M20;
			values[2][1] = _M21;
			values[2][2] = _M22;
			values[2][3] = _M23;

			values[3][0] = _M30;
			values[3][1] = _M31;
			values[3][2] = _M32;
			values[3][3] = _M33;

			return *this;
		}

		Matrix4f &scale(float scalar)
		{
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					values[i][j] *= scalar;
				}
			}
			return *this;
		}

		Matrix4f &transpose()
		{
			Matrix4f tmp;

			tmp.values[0][0] = values[0][0];
			tmp.values[0][1] = values[1][0];
			tmp.values[0][2] = values[2][0];
			tmp.values[0][3] = values[3][0];

			tmp.values[1][0] = values[0][1];
			tmp.values[1][1] = values[1][1];
			tmp.values[1][2] = values[2][1];
			tmp.values[1][3] = values[3][1];

			tmp.values[2][0] = values[0][2];
			tmp.values[2][1] = values[1][2];
			tmp.values[2][2] = values[2][2];
			tmp.values[2][3] = values[3][2];

			tmp.values[3][0] = values[0][3];
			tmp.values[3][1] = values[1][3];
			tmp.values[3][2] = values[2][3];
			tmp.values[3][3] = values[3][3];

			set(tmp);

			return *this;
		}

		Matrix4f &invert()
		{
			float tmp[4][4];
			float l_det = values[3][0] * values[2][1] * values[1][2] * values[0][3] - values[2][0] * values[3][1] * values[1][2] * values[0][3] - values[3][0] * values[1][1]
				* values[2][2] * values[0][3] + values[1][0] * values[3][1] * values[2][2] * values[0][3] + values[2][0] * values[1][1] * values[3][2] * values[0][3] - values[1][0]
				* values[2][1] * values[3][2] * values[0][3] - values[3][0] * values[2][1] * values[0][2] * values[1][3] + values[2][0] * values[3][1] * values[0][2] * values[1][3]
				+ values[3][0] * values[0][1] * values[2][2] * values[1][3] - values[0][0] * values[3][1] * values[2][2] * values[1][3] - values[2][0] * values[0][1] * values[3][2]
				* values[1][3] + values[0][0] * values[2][1] * values[3][2] * values[1][3] + values[3][0] * values[1][1] * values[0][2] * values[2][3] - values[1][0] * values[3][1]
				* values[0][2] * values[2][3] - values[3][0] * values[0][1] * values[1][2] * values[2][3] + values[0][0] * values[3][1] * values[1][2] * values[2][3] + values[1][0]
				* values[0][1] * values[3][2] * values[2][3] - values[0][0] * values[1][1] * values[3][2] * values[2][3] - values[2][0] * values[1][1] * values[0][2] * values[3][3]
				+ values[1][0] * values[2][1] * values[0][2] * values[3][3] + values[2][0] * values[0][1] * values[1][2] * values[3][3] - values[0][0] * values[2][1] * values[1][2]
				* values[3][3] - values[1][0] * values[0][1] * values[2][2] * values[3][3] + values[0][0] * values[1][1] * values[2][2] * values[3][3];

			if (l_det == 0) return *this;

			float inv_det = 1.0f / l_det;

			tmp[0][0] = values[1][2] * values[2][3] * values[3][1] - values[1][3] * values[2][2] * values[3][1] + values[1][3] * values[2][1] * values[3][2] - values[1][1]
				* values[2][3] * values[3][2] - values[1][2] * values[2][1] * values[3][3] + values[1][1] * values[2][2] * values[3][3];

			tmp[0][1] = values[0][3] * values[2][2] * values[3][1] - values[0][2] * values[2][3] * values[3][1] - values[0][3] * values[2][1] * values[3][2] + values[0][1]
				* values[2][3] * values[3][2] + values[0][2] * values[2][1] * values[3][3] - values[0][1] * values[2][2] * values[3][3];

			tmp[0][2] = values[0][2] * values[1][3] * values[3][1] - values[0][3] * values[1][2] * values[3][1] + values[0][3] * values[1][1] * values[3][2] - values[0][1]
				* values[1][3] * values[3][2] - values[0][2] * values[1][1] * values[3][3] + values[0][1] * values[1][2] * values[3][3];

			tmp[0][3] = values[0][3] * values[1][2] * values[2][1] - values[0][2] * values[1][3] * values[2][1] - values[0][3] * values[1][1] * values[2][2] + values[0][1]
				* values[1][3] * values[2][2] + values[0][2] * values[1][1] * values[2][3] - values[0][1] * values[1][2] * values[2][3];

			tmp[1][0] = values[1][3] * values[2][2] * values[3][0] - values[1][2] * values[2][3] * values[3][0] - values[1][3] * values[2][0] * values[3][2] + values[1][0]
				* values[2][3] * values[3][2] + values[1][2] * values[2][0] * values[3][3] - values[1][0] * values[2][2] * values[3][3];

			tmp[1][1] = values[0][2] * values[2][3] * values[3][0] - values[0][3] * values[2][2] * values[3][0] + values[0][3] * values[2][0] * values[3][2] - values[0][0]
				* values[2][3] * values[3][2] - values[0][2] * values[2][0] * values[3][3] + values[0][0] * values[2][2] * values[3][3];

			tmp[1][2] = values[0][3] * values[1][2] * values[3][0] - values[0][2] * values[1][3] * values[3][0] - values[0][3] * values[1][0] * values[3][2] + values[0][0]
				* values[1][3] * values[3][2] + values[0][2] * values[1][0] * values[3][3] - values[0][0] * values[1][2] * values[3][3];

			tmp[1][3] = values[0][2] * values[1][3] * values[2][0] - values[0][3] * values[1][2] * values[2][0] + values[0][3] * values[1][0] * values[2][2] - values[0][0]
				* values[1][3] * values[2][2] - values[0][2] * values[1][0] * values[2][3] + values[0][0] * values[1][2] * values[2][3];

			tmp[2][0] = values[1][1] * values[2][3] * values[3][0] - values[1][3] * values[2][1] * values[3][0] + values[1][3] * values[2][0] * values[3][1] - values[1][0]
				* values[2][3] * values[3][1] - values[1][1] * values[2][0] * values[3][3] + values[1][0] * values[2][1] * values[3][3];

			tmp[2][1] = values[0][3] * values[2][1] * values[3][0] - values[0][1] * values[2][3] * values[3][0] - values[0][3] * values[2][0] * values[3][1] + values[0][0]
				* values[2][3] * values[3][1] + values[0][1] * values[2][0] * values[3][3] - values[0][0] * values[2][1] * values[3][3];

			tmp[2][2] = values[0][1] * values[1][3] * values[3][0] - values[0][3] * values[1][1] * values[3][0] + values[0][3] * values[1][0] * values[3][1] - values[0][0]
				* values[1][3] * values[3][1] - values[0][1] * values[1][0] * values[3][3] + values[0][0] * values[1][1] * values[3][3];

			tmp[2][3] = values[0][3] * values[1][1] * values[2][0] - values[0][1] * values[1][3] * values[2][0] - values[0][3] * values[1][0] * values[2][1] + values[0][0]
				* values[1][3] * values[2][1] + values[0][1] * values[1][0] * values[2][3] - values[0][0] * values[1][1] * values[2][3];

			tmp[3][0] = values[1][2] * values[2][1] * values[3][0] - values[1][1] * values[2][2] * values[3][0] - values[1][2] * values[2][0] * values[3][1] + values[1][0]
				* values[2][2] * values[3][1] + values[1][1] * values[2][0] * values[3][2] - values[1][0] * values[2][1] * values[3][2];

			tmp[3][1] = values[0][1] * values[2][2] * values[3][0] - values[0][2] * values[2][1] * values[3][0] + values[0][2] * values[2][0] * values[3][1] - values[0][0]
				* values[2][2] * values[3][1] - values[0][1] * values[2][0] * values[3][2] + values[0][0] * values[2][1] * values[3][2];

			tmp[3][2] = values[0][2] * values[1][1] * values[3][0] - values[0][1] * values[1][2] * values[3][0] - values[0][2] * values[1][0] * values[3][1] + values[0][0]
				* values[1][2] * values[3][1] + values[0][1] * values[1][0] * values[3][2] - values[0][0] * values[1][1] * values[3][2];

			tmp[3][3] = values[0][1] * values[1][2] * values[2][0] - values[0][2] * values[1][1] * values[2][0] + values[0][2] * values[1][0] * values[2][1] - values[0][0]
				* values[1][2] * values[2][1] - values[0][1] * values[1][0] * values[2][2] + values[0][0] * values[1][1] * values[2][2];

			values[0][0] = tmp[0][0] * inv_det;
			values[0][1] = tmp[0][1] * inv_det;
			values[0][2] = tmp[0][2] * inv_det;
			values[0][3] = tmp[0][3] * inv_det;
			values[1][0] = tmp[1][0] * inv_det;
			values[1][1] = tmp[1][1] * inv_det;
			values[1][2] = tmp[1][2] * inv_det;
			values[1][3] = tmp[1][3] * inv_det;
			values[2][0] = tmp[2][0] * inv_det;
			values[2][1] = tmp[2][1] * inv_det;
			values[2][2] = tmp[2][2] * inv_det;
			values[2][3] = tmp[2][3] * inv_det;
			values[3][0] = tmp[3][0] * inv_det;
			values[3][1] = tmp[3][1] * inv_det;
			values[3][2] = tmp[3][2] * inv_det;
			values[3][3] = tmp[3][3] * inv_det;

			return *this;
		}

		friend ostream& operator<<(ostream& out, const Matrix4f &mat) // output
		{
			out << "[";
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					out << mat.values[i][j];

					if (j != 3)
						out << ", ";
				}

				if (i != 3)
					out << "\n";
			}
			out << "]";
			return out;
		}
	};
}
#endif