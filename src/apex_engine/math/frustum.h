#ifndef FRUSTUM_H
#define FRUSTUM_H

#include "matrix4f.h"
#include "vector4f.h"
#include "vector3f.h"
#include "boundingbox.h"

namespace apex
{
	class Frustum
	{
	private:
		Matrix4f vpMatrix;
		Vector4f planes[6];

		Vector3f tmp;

		float frustum[6][4];
	public:
		Frustum() {}

		void setViewProjectionMatrix(Matrix4f &matrix)
		{
			this->vpMatrix.set(matrix);
			//vpMatrix.transpose();

			Vector4f rows[4];

			for (int i = 0; i < 4; i++)
			{
				rows[i].x = vpMatrix.values[i][0];
				rows[i].y = vpMatrix.values[i][1];
				rows[i].z = vpMatrix.values[i][2];
				rows[i].w = vpMatrix.values[i][3];
			}

			planes[0].set(rows[3]).add(rows[0]).normalize();
			planes[1].set(rows[3]).subtract(rows[0]).normalize();
			planes[2].set(rows[3]).add(rows[1]).normalize();
			planes[3].set(rows[3]).subtract(rows[1]).normalize();
			planes[4].set(rows[3]).add(rows[2]).normalize();
			planes[5].set(rows[3]).subtract(rows[2]).normalize();
			


			vpMatrix.transpose();
			float *m_1d = vpMatrix.get1DArray();

			float t;
			frustum[0][0] = *(m_1d + 3) - *(m_1d + 0);
			frustum[0][1] = *(m_1d + 7) - *(m_1d + 4);
			frustum[0][2] = *(m_1d + 11) - *(m_1d + 8);
			frustum[0][3] = *(m_1d + 15) - *(m_1d + 12);

			t = sqrt(frustum[0][0] * frustum[0][0] + frustum[0][1] * frustum[0][1] + frustum[0][2] * frustum[0][2]);
			frustum[0][0] /= t;
			frustum[0][1] /= t;
			frustum[0][2] /= t;
			frustum[0][3] /= t;

			frustum[1][0] = *(m_1d + 3) + *(m_1d + 0);
			frustum[1][1] = *(m_1d + 7) + *(m_1d + 4);
			frustum[1][2] = *(m_1d + 11) + *(m_1d + 8);
			frustum[1][3] = *(m_1d + 15) + *(m_1d + 12);

			t = sqrt(frustum[1][0] * frustum[1][0] + frustum[1][1] * frustum[1][1] + frustum[1][2] * frustum[1][2]);
			frustum[1][0] /= t;
			frustum[1][1] /= t;
			frustum[1][2] /= t;
			frustum[1][3] /= t;

			frustum[2][0] = *(m_1d + 3) + *(m_1d + 1);
			frustum[2][1] = *(m_1d + 7) + *(m_1d + 5);
			frustum[2][2] = *(m_1d + 11) + *(m_1d + 9);
			frustum[2][3] = *(m_1d + 15) + *(m_1d + 13);

			t = sqrt(frustum[2][0] * frustum[2][0] + frustum[2][1] * frustum[2][1] + frustum[2][2] * frustum[2][2]);
			frustum[2][0] /= t;
			frustum[2][1] /= t;
			frustum[2][2] /= t;
			frustum[2][3] /= t;

			frustum[3][0] = *(m_1d + 3) - *(m_1d + 1);
			frustum[3][1] = *(m_1d + 7) - *(m_1d + 5);
			frustum[3][2] = *(m_1d + 11) - *(m_1d + 9);
			frustum[3][3] = *(m_1d + 15) - *(m_1d + 13);

			t = sqrt(frustum[3][0] * frustum[3][0] + frustum[3][1] * frustum[3][1] + frustum[3][2] * frustum[3][2]);
			frustum[3][0] /= t;
			frustum[3][1] /= t;
			frustum[3][2] /= t;
			frustum[3][3] /= t;

			frustum[4][0] = *(m_1d + 3) - *(m_1d + 2);
			frustum[4][1] = *(m_1d + 7) - *(m_1d + 6);
			frustum[4][2] = *(m_1d + 11) - *(m_1d + 10);
			frustum[4][3] = *(m_1d + 15) - *(m_1d + 14);

			t = sqrt(frustum[4][0] * frustum[4][0] + frustum[4][1] * frustum[4][1] + frustum[4][2] * frustum[4][2]);
			frustum[4][0] /= t;
			frustum[4][1] /= t;
			frustum[4][2] /= t;
			frustum[4][3] /= t;

			frustum[5][0] = *(m_1d + 3) + *(m_1d + 2);
			frustum[5][1] = *(m_1d + 7) + *(m_1d + 6);
			frustum[5][2] = *(m_1d + 11) + *(m_1d + 10);
			frustum[5][3] = *(m_1d + 15) + *(m_1d + 14);

			t = sqrt(frustum[5][0] * frustum[5][0] + frustum[5][1] * frustum[5][1] + frustum[5][2] * frustum[5][2]);
			frustum[5][0] /= t;
			frustum[5][1] /= t;
			frustum[5][2] /= t;
			frustum[5][3] /= t;
		}

		const Vector4f &getPlane(int i)
		{
			return planes[i];
		}

		bool intersectPoint(const Vector3f &translation)
		{
			tmp.set(translation);

			/*for (int i = 0; i < 6; i++)
			{
				Vector4f plane = planes[i];

				if (plane.x * tmp.x + plane.y * tmp.y + plane.z * tmp.z + plane.w <= 0)
					return false;
			}
			return true;*/
			for (int i = 0; i < 6; i++)
			{
				float dist = frustum[i][0] * tmp.x + frustum[i][1] * tmp.y + frustum[i][2] * tmp.z + frustum[i][3];
				
				if (dist <= 0)
				{
					return false;
				}
			}
			return true;
		}

		bool intersectSphere(const Vector3f &center, const float radius)
		{
			tmp.set(center);
			tmp.transform(vpMatrix);

			for (int i = 0; i < 6; i++)
			{
				Vector4f plane = planes[i];

				if (plane.x * tmp.x + plane.y * tmp.y + plane.z * tmp.z + plane.w <= -radius)
					return false;
			}

			return true;
		}

		bool intersectAABB(const BoundingBox &aabb)
		{
			for (int i = 0; i < BoundingBox::NUM_CORNERS; i++)
			{
				if (intersectPoint(aabb.getCorner(i)))
					return true;
			}
			return false;
		}
	};
}
#endif