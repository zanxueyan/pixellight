//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <UnitTest++/UnitTest++.h>
#include <PLMath/Matrix4x4.h>
#include <PLMath/Vector3.h>
#include <PLMath/Vector4.h>
#include <PLMath/EulerAngles.h>

using namespace PLMath;

/*
* Naming Convention for SUITE:
* CLASSNAME
*/
SUITE(Matrix4x4) {
	/*
	* Naming Convention for METHOD:
	* METHODNAME_SCENARIO
	*/

	// Our Array Test Fixture :)
	struct ConstructTest
	{
		ConstructTest() {
			/* some setup */
			float val = 0.0f;
			for (int i=0; i<16; i++, val+=1.0f)
				fT[i]=val;
		}
		~ConstructTest() {
			/* some teardown */
		}

		// Container for testing
		float fT[16];
		Matrix4x4 mM, mMT;
		Vector3 vV3;
		Vector4 vV4;
	};

	bool CheckAxisAngle(float fX, float fY, float fZ, float fAngle, float fExpectedAngle)
	{
		float fXT, fYT, fZT, fAngleT;
		Matrix4x4 mRot;

		// Degree to radian
		fAngle         = static_cast<float>(fAngle*Math::DegToRad);
		fExpectedAngle = static_cast<float>(fExpectedAngle*Math::DegToRad);

		mRot.FromAxisAngle(fX, fY, fZ, fAngle);
		mRot.ToAxisAngle(fXT, fYT, fZT, fAngleT);
		if (Math::AreEqual(fX, fXT) && Math::AreEqual(fY, fYT) && Math::AreEqual(fZ, fZT) &&
			Math::AreEqual(fAngleT, fExpectedAngle))
			return true; // Success
		else return false; // Error!
	}

	// Matrix constructors & copy
	TEST_FIXTURE(ConstructTest, Constructors_and_Getter) {
		// Matrix must be identity
		CHECK_EQUAL(1.0f, mM.xx);
		CHECK_EQUAL(0.0f, mM.xy);
		CHECK_EQUAL(0.0f, mM.xz);
		CHECK_EQUAL(0.0f, mM.xw);
		CHECK_EQUAL(0.0f, mM.yx);
		CHECK_EQUAL(1.0f, mM.yy);
		CHECK_EQUAL(0.0f, mM.yz);
		CHECK_EQUAL(0.0f, mM.yw);
		CHECK_EQUAL(0.0f, mM.zx);
		CHECK_EQUAL(0.0f, mM.zy);
		CHECK_EQUAL(1.0f, mM.zz);
		CHECK_EQUAL(0.0f, mM.zw);
		CHECK_EQUAL(0.0f, mM.wx);
		CHECK_EQUAL(0.0f, mM.wy);
		CHECK_EQUAL(0.0f, mM.wz);
		CHECK_EQUAL(1.0f, mM.ww);

		// Matrix4x4(const float[])
		mM = Matrix4x4(fT);
		// fM[16]
		CHECK_EQUAL(0.0f, mM.fM[0]);
		CHECK_EQUAL(4.0f, mM.fM[4]);
		CHECK_EQUAL(8.0f, mM.fM[ 8]);
		CHECK_EQUAL(12.0f, mM.fM[12]);
		CHECK_EQUAL(1.0f, mM.fM[1]);
		CHECK_EQUAL(5.0f, mM.fM[5]);
		CHECK_EQUAL(9.0f, mM.fM[ 9]);
		CHECK_EQUAL(13.0f, mM.fM[13]);
		CHECK_EQUAL(2.0f, mM.fM[2]);
		CHECK_EQUAL(6.0f, mM.fM[6]);
		CHECK_EQUAL(10.0f, mM.fM[10]);
		CHECK_EQUAL(14.0f, mM.fM[14]);
		CHECK_EQUAL(3.0f, mM.fM[3]);
		CHECK_EQUAL(7.0f, mM.fM[7]);
		CHECK_EQUAL(11.0f, mM.fM[11]);
		CHECK_EQUAL(15.0f, mM.fM[15]);

		// The entry of the matrix in row r (0 <= r <= 3) and column c (0 <= c <= 3) is
		// stored at index i = r+4*c (0 <= i <= 15).
		CHECK_EQUAL(0.0f, mM.fM[0+4*0]);
		CHECK_EQUAL(4.0f, mM.fM[0+4*1]);
		CHECK_EQUAL(8.0f, mM.fM[0+4*2]);
		CHECK_EQUAL(12.0f, mM.fM[0+4*3]);
		CHECK_EQUAL(1.0f, mM.fM[1+4*0]);
		CHECK_EQUAL(5.0f, mM.fM[1+4*1]);
		CHECK_EQUAL(9.0f, mM.fM[1+4*2]);
		CHECK_EQUAL(13.0f, mM.fM[1+4*3]);
		CHECK_EQUAL(2.0f, mM.fM[2+4*0]);
		CHECK_EQUAL(6.0f, mM.fM[2+4*1]);
		CHECK_EQUAL(10.0f, mM.fM[2+4*2]);
		CHECK_EQUAL(14.0f, mM.fM[2+4*3]);
		CHECK_EQUAL(3.0f, mM.fM[3+4*0]);
		CHECK_EQUAL(7.0f, mM.fM[3+4*1]);
		CHECK_EQUAL(11.0f, mM.fM[3+4*2]);
		CHECK_EQUAL(15.0f, mM.fM[3+4*3]);

		// xx, xy...
		CHECK_EQUAL(0.0f, mM.xx);
		CHECK_EQUAL(4.0f, mM.xy);
		CHECK_EQUAL(8.0f, mM.xz);
		CHECK_EQUAL(12.0f, mM.xw);
		CHECK_EQUAL(1.0f, mM.yx);
		CHECK_EQUAL(5.0f, mM.yy);
		CHECK_EQUAL(9.0f, mM.yz);
		CHECK_EQUAL(13.0f, mM.yw);
		CHECK_EQUAL(2.0f, mM.zx);
		CHECK_EQUAL(6.0f, mM.zy);
		CHECK_EQUAL(10.0f, mM.zz);
		CHECK_EQUAL(14.0f, mM.zw);
		CHECK_EQUAL(3.0f, mM.wx);
		CHECK_EQUAL(7.0f, mM.wy);
		CHECK_EQUAL(11.0f, mM.wz);
		CHECK_EQUAL(15.0f, mM.ww);

		// fM44[4][4]
		CHECK_EQUAL(0.0f, mM.fM44[0][0]);
		CHECK_EQUAL(4.0f, mM.fM44[1][0]);
		CHECK_EQUAL(8.0f, mM.fM44[2][0]);
		CHECK_EQUAL(12.0f, mM.fM44[3][0]);
		CHECK_EQUAL(1.0f, mM.fM44[0][1]);
		CHECK_EQUAL(5.0f, mM.fM44[1][1]);
		CHECK_EQUAL(9.0f, mM.fM44[2][1]);
		CHECK_EQUAL(13.0f, mM.fM44[3][1]);
		CHECK_EQUAL(2.0f, mM.fM44[0][2]);
		CHECK_EQUAL(6.0f, mM.fM44[1][2]);
		CHECK_EQUAL(10.0f, mM.fM44[2][2]);
		CHECK_EQUAL(14.0f, mM.fM44[3][2]);
		CHECK_EQUAL(3.0f, mM.fM44[0][3]);
		CHECK_EQUAL(7.0f, mM.fM44[1][3]);
		CHECK_EQUAL(11.0f, mM.fM44[2][3]);
		CHECK_EQUAL(15.0f, mM.fM44[3][3]);

		// Matrix4x4(float fXX, float fXY, float fXZ, float fXW,
		//			 float fYX, float fYY, float fYZ, float fYW,
		//			 float fZX, float fZY, float fZZ, float fZW,
		//			 float fWX, float fWY, float fWZ, float fWW)
		mM = Matrix4x4( 0.0f, 0.1f, 0.2f, 0.3f,
			1.0f, 1.1f, 1.2f, 1.3f,
			2.0f, 2.1f, 2.2f, 2.3f,
			3.0f, 3.1f, 3.2f, 3.3f);
		CHECK_EQUAL(0.0f, mM.xx);
		CHECK_EQUAL(0.1f, mM.xy);
		CHECK_EQUAL(0.2f, mM.xz);
		CHECK_EQUAL(0.3f, mM.xw);
		CHECK_EQUAL(1.0f, mM.yx);
		CHECK_EQUAL(1.1f, mM.yy);
		CHECK_EQUAL(1.2f, mM.yz);
		CHECK_EQUAL(1.3f, mM.yw);
		CHECK_EQUAL(2.0f, mM.zx);
		CHECK_EQUAL(2.1f, mM.zy);
		CHECK_EQUAL(2.2f, mM.zz);
		CHECK_EQUAL(2.3f, mM.zw);
		CHECK_EQUAL(3.0f, mM.wx);
		CHECK_EQUAL(3.1f, mM.wy);
		CHECK_EQUAL(3.2f, mM.wz);
		CHECK_EQUAL(3.3f, mM.ww);
		CHECK_EQUAL(0.0f, mM.fM[0]);
		CHECK_EQUAL(0.1f, mM.fM[4]);
		CHECK_EQUAL(0.2f, mM.fM[ 8]);
		CHECK_EQUAL(0.3f, mM.fM[12]);
		CHECK_EQUAL(1.0f, mM.fM[1]);
		CHECK_EQUAL(1.1f, mM.fM[5]);
		CHECK_EQUAL(1.2f, mM.fM[ 9]);
		CHECK_EQUAL(1.3f, mM.fM[13]);
		CHECK_EQUAL(2.0f, mM.fM[2]);
		CHECK_EQUAL(2.1f, mM.fM[6]);
		CHECK_EQUAL(2.2f, mM.fM[10]);
		CHECK_EQUAL(2.3f, mM.fM[14]);
		CHECK_EQUAL(3.0f, mM.fM[3]);
		CHECK_EQUAL(3.1f, mM.fM[7]);
		CHECK_EQUAL(3.2f, mM.fM[11]);
		CHECK_EQUAL(3.3f, mM.fM[15]);
	}

	// Static variables
	TEST_FIXTURE(ConstructTest, Static_Variables) {
		CHECK_EQUAL(0.0f, Matrix4x4::Zero.xx);
		CHECK_EQUAL(0.0f, Matrix4x4::Zero.xy);
		CHECK_EQUAL(0.0f, Matrix4x4::Zero.xz);
		CHECK_EQUAL(0.0f, Matrix4x4::Zero.xw);
		CHECK_EQUAL(0.0f, Matrix4x4::Zero.yx);
		CHECK_EQUAL(0.0f, Matrix4x4::Zero.yy);
		CHECK_EQUAL(0.0f, Matrix4x4::Zero.yz);
		CHECK_EQUAL(0.0f, Matrix4x4::Zero.yw);
		CHECK_EQUAL(0.0f, Matrix4x4::Zero.zx);
		CHECK_EQUAL(0.0f, Matrix4x4::Zero.zy);
		CHECK_EQUAL(0.0f, Matrix4x4::Zero.zz);
		CHECK_EQUAL(0.0f, Matrix4x4::Zero.zw);
		CHECK_EQUAL(0.0f, Matrix4x4::Zero.wx);
		CHECK_EQUAL(0.0f, Matrix4x4::Zero.wy);
		CHECK_EQUAL(0.0f, Matrix4x4::Zero.wz);
		CHECK_EQUAL(0.0f, Matrix4x4::Zero.ww);

		CHECK_EQUAL(1.0f, Matrix4x4::Identity.xx);
		CHECK_EQUAL(0.0f, Matrix4x4::Identity.xy);
		CHECK_EQUAL(0.0f, Matrix4x4::Identity.xz);
		CHECK_EQUAL(0.0f, Matrix4x4::Identity.xw);
		CHECK_EQUAL(0.0f, Matrix4x4::Identity.yx);
		CHECK_EQUAL(1.0f, Matrix4x4::Identity.yy);
		CHECK_EQUAL(0.0f, Matrix4x4::Identity.yz);
		CHECK_EQUAL(0.0f, Matrix4x4::Identity.yw);
		CHECK_EQUAL(0.0f, Matrix4x4::Identity.zx);
		CHECK_EQUAL(0.0f, Matrix4x4::Identity.zy);
		CHECK_EQUAL(1.0f, Matrix4x4::Identity.zz);
		CHECK_EQUAL(0.0f, Matrix4x4::Identity.zw);
		CHECK_EQUAL(0.0f, Matrix4x4::Identity.wx);
		CHECK_EQUAL(0.0f, Matrix4x4::Identity.wy);
		CHECK_EQUAL(0.0f, Matrix4x4::Identity.wz);
		CHECK_EQUAL(1.0f, Matrix4x4::Identity.ww);
	}

	// Operators
	// * Vector3
	TEST_FIXTURE(ConstructTest, Multiplication_Vector3) {
		// 90�
		vV3 = Vector3(1.0f, 0.0f, 0.0f);
		mM.FromEulerAngleY(static_cast<float>(90.0f*Math::DegToRad));
		vV3 = mM*vV3;
		CHECK_CLOSE(0.0f, vV3.x, Math::Epsilon);
		CHECK_CLOSE(0.0f, vV3.y, Math::Epsilon);
		CHECK_CLOSE(-1.0f, vV3.z, Math::Epsilon);

		// -90�
		vV3 = Vector3(1.0f, 0.0f, 0.0f);
		mM.FromEulerAngleY(-static_cast<float>(90.0f*Math::DegToRad));
		vV3 *= mM;
		CHECK_CLOSE(0.0f, vV3.x, Math::Epsilon);
		CHECK_CLOSE(0.0f, vV3.y, Math::Epsilon);
		CHECK_CLOSE(1.0f, vV3.z, Math::Epsilon);

		// -90� + translation (2, 3, 4)
		vV3 = Vector3(1.0f, 0.0f, 0.0f);
		mM.FromEulerAngleY(-static_cast<float>(90.0f*Math::DegToRad));
		mM.SetTranslation(2.0f, 3.0f, 4.0f);
		vV3 = mM*vV3;
		CHECK_CLOSE(2.0f, vV3.x, Math::Epsilon);
		CHECK_CLOSE(3.0f, vV3.y, Math::Epsilon);
		CHECK_CLOSE(5.0f, vV3.z, Math::Epsilon);
	}

	// Matrix operations
	// IsZero()
	TEST_FIXTURE(ConstructTest, IsZero) {
		mM = Matrix4x4::Zero;
		CHECK(mM.IsZero());

		mM.yz = 0.001f;
		CHECK(!(mM.IsZero()));

		mM.yz = static_cast<float>(Math::Epsilon);
		CHECK(mM.IsZero());
	}

	// IsTrueZero()
	TEST_FIXTURE(ConstructTest, IsTrueZero) {
		mM = Matrix4x4::Zero;
		CHECK(mM.IsTrueZero());

		mM.yz = 0.001f;
		CHECK(!(mM.IsTrueZero()));

		mM.yz = static_cast<float>(Math::Epsilon);
		CHECK(!(mM.IsTrueZero()));
	}

	// SetZero()
	TEST_FIXTURE(ConstructTest, SetZero) {
		mM.yz = 0.001f;
		mM.xx = 0.101f;
		mM.SetZero();
		CHECK_EQUAL(0.0f, mM.xx);
		CHECK_EQUAL(0.0f, mM.xy);
		CHECK_EQUAL(0.0f, mM.xz);
		CHECK_EQUAL(0.0f, mM.xw);
		CHECK_EQUAL(0.0f, mM.yx);
		CHECK_EQUAL(0.0f, mM.yy);
		CHECK_EQUAL(0.0f, mM.yz);
		CHECK_EQUAL(0.0f, mM.yw);
		CHECK_EQUAL(0.0f, mM.zx);
		CHECK_EQUAL(0.0f, mM.zy);
		CHECK_EQUAL(0.0f, mM.zz);
		CHECK_EQUAL(0.0f, mM.zw);
		CHECK_EQUAL(0.0f, mM.wx);
		CHECK_EQUAL(0.0f, mM.wy);
		CHECK_EQUAL(0.0f, mM.wz);
		CHECK_EQUAL(0.0f, mM.ww);
	}

	// IsIdentity()
	TEST_FIXTURE(ConstructTest, IsIdentity) {
		mM = Matrix4x4::Identity;
		CHECK(mM.IsIdentity());

		mM.yz = 0.001f;
		CHECK(!(mM.IsIdentity()));

		mM.yz = static_cast<float>(Math::Epsilon);
		CHECK(mM.IsIdentity());
	}

	// IsTrueIdentity()
	TEST_FIXTURE(ConstructTest, IsTrueIdentity) {
		mM = Matrix4x4::Identity;
		CHECK(mM.IsTrueIdentity());

		mM.yz = 0.001f;
		CHECK(!(mM.IsTrueIdentity()));

		mM.yz = static_cast<float>(Math::Epsilon);
		CHECK(!(mM.IsTrueIdentity()));
	}

	// SetIdentity()
	TEST_FIXTURE(ConstructTest, SetIdentity) {
		mM.yz = 0.001f;
		mM.xx = 0.101f;
		mM.SetIdentity();
		CHECK_EQUAL(1.0f, mM.xx);
		CHECK_EQUAL(0.0f, mM.xy);
		CHECK_EQUAL(0.0f, mM.xz);
		CHECK_EQUAL(0.0f, mM.xw);
		CHECK_EQUAL(0.0f, mM.yx);
		CHECK_EQUAL(1.0f, mM.yy);
		CHECK_EQUAL(0.0f, mM.yz);
		CHECK_EQUAL(0.0f, mM.yw);
		CHECK_EQUAL(0.0f, mM.zx);
		CHECK_EQUAL(0.0f, mM.zy);
		CHECK_EQUAL(1.0f, mM.zz);
		CHECK_EQUAL(0.0f, mM.zw);
		CHECK_EQUAL(0.0f, mM.wx);
		CHECK_EQUAL(0.0f, mM.wy);
		CHECK_EQUAL(0.0f, mM.wz);
		CHECK_EQUAL(1.0f, mM.ww);
	}

	// Set()
	TEST_FIXTURE(ConstructTest, Set) {
		mM.Set( -0.1f,  -1.0f,  -2.0f,  -3.0f,
			-4.0f,  -5.0f,  -6.0f,  -7.0f,
			-8.0f,  -9.0f, -10.0f, -11.0f,
			-12.0f, -13.0f, -14.0f, -15.0f);
		CHECK_EQUAL(-0.1f, mM.xx);
		CHECK_EQUAL(-1.0f, mM.xy);
		CHECK_EQUAL(-2.0f, mM.xz);
		CHECK_EQUAL(-3.0f, mM.xw);
		CHECK_EQUAL(-4.0f, mM.yx);
		CHECK_EQUAL(-5.0f, mM.yy);
		CHECK_EQUAL(-6.0f, mM.yz);
		CHECK_EQUAL(-7.0f, mM.yw);
		CHECK_EQUAL(-8.0f, mM.zx);
		CHECK_EQUAL(-9.0f, mM.zy);
		CHECK_EQUAL(-10.0f, mM.zz);
		CHECK_EQUAL(-11.0f, mM.zw);
		CHECK_EQUAL(-12.0f, mM.wx);
		CHECK_EQUAL(-13.0f, mM.wy);
		CHECK_EQUAL(-14.0f, mM.wz);
		CHECK_EQUAL(-15.0f, mM.ww);
	}

	// GetRow()
	TEST_FIXTURE(ConstructTest, GetRow) {
		mM = fT;
		vV4 = mM.GetRow(0);
		CHECK_EQUAL(0.0f, vV4.x);
		CHECK_EQUAL(4.0f, vV4.y);
		CHECK_EQUAL(8.0f, vV4.z);
		CHECK_EQUAL(12.0f, vV4.w);

		vV4 = mM.GetRow(1);
		CHECK_EQUAL(1.0f, vV4.x);
		CHECK_EQUAL(5.0f, vV4.y);
		CHECK_EQUAL(9.0f, vV4.z);
		CHECK_EQUAL(13.0f, vV4.w);

		vV4 = mM.GetRow(2);
		CHECK_EQUAL(2.0f, vV4.x);
		CHECK_EQUAL(6.0f, vV4.y);
		CHECK_EQUAL(10.0f, vV4.z);
		CHECK_EQUAL(14.0f, vV4.w);

		vV4 = mM.GetRow(3);
		CHECK_EQUAL(3.0f, vV4.x);
		CHECK_EQUAL(7.0f, vV4.y);
		CHECK_EQUAL(11.0f, vV4.z);
		CHECK_EQUAL(15.0f, vV4.w);
	}

	// SetRow()
	TEST_FIXTURE(ConstructTest, SetRow) {
		mM.SetRow(0, Vector4(-0.1f, -4.0f, -8.0f, -12.0f));
		CHECK_EQUAL(-0.1f, mM.xx);
		CHECK_EQUAL(-4.0f, mM.xy);
		CHECK_EQUAL(-8.0f, mM.xz);
		CHECK_EQUAL(-12.0f, mM.xw);

		mM.SetRow(1, Vector4(-1.0f, -5.0f, -9.0f, -13.0f));
		CHECK_EQUAL(-1.0f, mM.yx);
		CHECK_EQUAL(-5.0f, mM.yy);
		CHECK_EQUAL(-9.0f, mM.yz);
		CHECK_EQUAL(-13.0f, mM.yw);

		mM.SetRow(2, Vector4(-2.0f, -6.0f, -10.0f, -14.0f));
		CHECK_EQUAL(-2.0f, mM.zx);
		CHECK_EQUAL(-6.0f, mM.zy);
		CHECK_EQUAL(-10.0f, mM.zz);
		CHECK_EQUAL(-14.0f, mM.zw);

		mM.SetRow(3, Vector4(-3.0f, -7.0f, -11.0f, -15.0f));
		CHECK_EQUAL(-3.0f, mM.wx);
		CHECK_EQUAL(-7.0f, mM.wy);
		CHECK_EQUAL(-11.0f, mM.wz);
		CHECK_EQUAL(-15.0f, mM.ww);
	}

	// GetColumn()
	TEST_FIXTURE(ConstructTest, GetColumn) {
		mM = fT;
		vV4 = mM.GetColumn(0);
		CHECK_EQUAL(0.0f, vV4.x);
		CHECK_EQUAL(1.0f, vV4.y);
		CHECK_EQUAL(2.0f, vV4.z);
		CHECK_EQUAL(3.0f, vV4.w);

		vV4 = mM.GetColumn(1);
		CHECK_EQUAL(4.0f, vV4.x);
		CHECK_EQUAL(5.0f, vV4.y);
		CHECK_EQUAL(6.0f, vV4.z);
		CHECK_EQUAL(7.0f, vV4.w);

		vV4 = mM.GetColumn(2);
		CHECK_EQUAL(8.0f, vV4.x);
		CHECK_EQUAL(9.0f, vV4.y);
		CHECK_EQUAL(10.0f, vV4.z);
		CHECK_EQUAL(11.0f, vV4.w);

		vV4 = mM.GetColumn(3);
		CHECK_EQUAL(12.0f, vV4.x);
		CHECK_EQUAL(13.0f, vV4.y);
		CHECK_EQUAL(14.0f, vV4.z);
		CHECK_EQUAL(15.0f, vV4.w);
	}

	// SetColumn()
	TEST_FIXTURE(ConstructTest, SetColumn) {
		mM.SetColumn(0, Vector4(-0.1f, -1.0f, -2.0f, -3.0f));
		CHECK_EQUAL(-0.1f, mM.xx);
		CHECK_EQUAL(-1.0f, mM.yx);
		CHECK_EQUAL(-2.0f, mM.zx);
		CHECK_EQUAL(-3.0f, mM.wx);

		mM.SetColumn(1, Vector4(-4.0f, -5.0f, -6.0f, -7.0f));
		CHECK_EQUAL(-4.0f, mM.xy);
		CHECK_EQUAL(-5.0f, mM.yy);
		CHECK_EQUAL(-6.0f, mM.zy);
		CHECK_EQUAL(-7.0f, mM.wy);

		mM.SetColumn(2, Vector4(-8.0f, -9.0f, -10.0f, -11.0f));
		CHECK_EQUAL(-8.0f, mM.xz);
		CHECK_EQUAL(-9.0f, mM.yz);
		CHECK_EQUAL(-10.0f, mM.zz);
		CHECK_EQUAL(-11.0f, mM.wz);

		mM.SetColumn(3, Vector4(-12.0f, -13.0f, -14.0f, -15.0f));
		CHECK_EQUAL(-12.0f, mM.xw);
		CHECK_EQUAL(-13.0f, mM.yw);
		CHECK_EQUAL(-14.0f, mM.zw);
		CHECK_EQUAL(-15.0f, mM.ww);
	}

	// IsSymmetric()
	TEST_FIXTURE(ConstructTest, IsSymmetric) {
		mM = Matrix4x4::Identity;
		CHECK(mM.IsSymmetric());

		mM.xx = 4.0f;
		CHECK(mM.IsSymmetric());

		mM.xy = 4.0f;
		CHECK(!(mM.IsSymmetric()));
	}

	// IsOrthogonal()
	TEST_FIXTURE(ConstructTest, IsOrthogonal) {
		mM = Matrix4x4::Identity;
		CHECK(mM.IsOrthogonal());

		mM.yw = 4.0f;
		CHECK(!mM.IsOrthogonal());

		mM.yw = 0.0f;
		CHECK(mM.IsOrthogonal());
	}

	// IsRotationMatrix()
	TEST_FIXTURE(ConstructTest, IsRotationMatrix) {
		mM = Matrix4x4::Identity;
		CHECK(mM.IsRotationMatrix());

		mM.xx = 4.0f;
		CHECK(!(mM.IsRotationMatrix()));
	}

	// GetTrace()
	TEST_FIXTURE(ConstructTest, GetTrace) {
		CHECK_EQUAL(0.0f, Matrix4x4::Zero.GetTrace());
		CHECK_EQUAL(4.0f, Matrix4x4::Identity.GetTrace());

		mM = Matrix4x4::Identity;
		mM.xy = 1.0f;
		CHECK_EQUAL(4.0f, mM.GetTrace());
	}

	// GetDeterminant()
	TEST_FIXTURE(ConstructTest, GetDeterminant) {
		CHECK_EQUAL(0.0f, Matrix4x4::Zero.GetDeterminant());
		CHECK_EQUAL(1.0f, Matrix4x4::Identity.GetDeterminant());
	}

	// Transpose()
	TEST_FIXTURE(ConstructTest, Transpose) {
		mM = Matrix4x4::Identity;
		mM.Transpose();
		CHECK(Matrix4x4::Identity == mM);
	}

	// GetTransposed()
	TEST_FIXTURE(ConstructTest, GetTransposed) {
		CHECK(Matrix4x4::Identity == Matrix4x4::Identity.GetTransposed());
	}

	// Invert()
	TEST_FIXTURE(ConstructTest, Invert) {
		mM = Matrix4x4::Identity;
		mM.Invert();
		CHECK(Matrix4x4::Identity == mM);
	}

	// GetInverted()
	TEST_FIXTURE(ConstructTest, GetInverted) {
		CHECK(Matrix4x4::Identity == Matrix4x4::Identity.GetInverted());
	}

	// Scale
	// GetScale(float fX, float fY, float fZ)
	TEST_FIXTURE(ConstructTest, GetScale_Float) {
		// Identity matrix
		vV3 = Vector3::Zero;
		Matrix4x4::Identity.GetScale(vV3.x, vV3.y, vV3.z);
		CHECK_EQUAL(1.0f, vV3.x);
		CHECK_EQUAL(1.0f, vV3.y);
		CHECK_EQUAL(1.0f, vV3.z);

		// Null matrix
		vV3 = Vector3::Zero;
		Matrix4x4::Zero.GetScale(vV3.x, vV3.y, vV3.z);
		CHECK_EQUAL(0.0f, vV3.x);
		CHECK_EQUAL(0.0f, vV3.y);
		CHECK_EQUAL(0.0f, vV3.z);

		// Any matrix
		vV3 = Vector3::Zero;
		mM.SetTranslationMatrix(1.0f, 2.0f, 3.0f);
		EulerAngles::ToMatrix(1.0f, 2.0f, 3.0f, mMT);
		mM *= mMT;
		mMT.SetScaleMatrix(1.0f, 2.0f, 3.0f);
		mM *= mMT;
		mM.GetScale(vV3.x, vV3.y, vV3.z);
		CHECK_CLOSE(1.0f, vV3.x, 0.000001f);
		CHECK_CLOSE(2.0f, vV3.y, 0.000001f);
		CHECK_CLOSE(3.0f, vV3.z, 0.000001f);
	}

	// GetXAxis()
	TEST_FIXTURE(ConstructTest, GetXAxis) {
		vV3 = Matrix4x4::Identity.GetXAxis();
		CHECK_EQUAL(1.0f, vV3.x);
		CHECK_EQUAL(0.0f, vV3.y);
		CHECK_EQUAL(0.0f, vV3.z);
	}

	// GetYAxis()
	TEST_FIXTURE(ConstructTest, GetYAxis) {
		vV3 = Matrix4x4::Identity.GetYAxis();
		CHECK_EQUAL(0.0f, vV3.x);
		CHECK_EQUAL(1.0f, vV3.y);
		CHECK_EQUAL(0.0f, vV3.z);
	}

	// GetZAxis()
	TEST_FIXTURE(ConstructTest, GetZAxis) {
		vV3 = Matrix4x4::Identity.GetZAxis();
		CHECK_EQUAL(0.0f, vV3.x);
		CHECK_EQUAL(0.0f, vV3.y);
		CHECK_EQUAL(1.0f, vV3.z);
	}

	// Rotation
	// ToAxisAngle() and FromAxisAngle()
	TEST_FIXTURE(ConstructTest, ToAxisAngle_and_FromAxisAngle) {
		// Check only x rotation
		// [TODO] Some tests will fail...
		//	if (!CheckAxisAngle(1.0f, 0.0f, 0.0f,   0.0f,   0.0f)) bResult = false;
		CHECK(CheckAxisAngle(1.0f, 0.0f, 0.0f,  45.0f,  45.0f));
		//	if (!CheckAxisAngle(1.0f, 0.0f, 0.0f, -45.0f,  45.0f)) bResult = false;
		CHECK(CheckAxisAngle(1.0f, 0.0f, 0.0f,  90.0f,  90.0f));
		CHECK(CheckAxisAngle(1.0f, 0.0f, 0.0f, 135.0f, 135.0f));
		CHECK(CheckAxisAngle(1.0f, 0.0f, 0.0f, 180.0f, 180.0f));
		//	if (!CheckAxisAngle(1.0f, 0.0f, 0.0f, 225.0f, 225.0f)) bResult = false;
		//	if (!CheckAxisAngle(1.0f, 0.0f, 0.0f, 270.0f, 270.0f)) bResult = false;
		//	if (!CheckAxisAngle(1.0f, 0.0f, 0.0f, 315.0f, 315.0f)) bResult = false;
		//	if (!CheckAxisAngle(1.0f, 0.0f, 0.0f, 360.0f, 360.0f)) bResult = false;
		// Check only y rotation
		//	if (!CheckAxisAngle(0.0f, 1.0f, 0.0f,   0.0f,   0.0f)) bResult = false;
		CHECK(CheckAxisAngle(0.0f, 1.0f, 0.0f,  45.0f,  45.0f));
		//	if (!CheckAxisAngle(0.0f, 1.0f, 0.0f, -45.0f,  45.0f)) bResult = false;
		CHECK(CheckAxisAngle(0.0f, 1.0f, 0.0f,  90.0f,  90.0f));
		CHECK(CheckAxisAngle(0.0f, 1.0f, 0.0f, 135.0f, 135.0f));
		CHECK(CheckAxisAngle(0.0f, 1.0f, 0.0f, 180.0f, 180.0f));
		//	if (!CheckAxisAngle(0.0f, 1.0f, 0.0f, 225.0f, 225.0f)) bResult = false;
		//	if (!CheckAxisAngle(0.0f, 1.0f, 0.0f, 270.0f, 270.0f)) bResult = false;
		//	if (!CheckAxisAngle(0.0f, 1.0f, 0.0f, 315.0f, 315.0f)) bResult = false;
		//	if (!CheckAxisAngle(0.0f, 1.0f, 0.0f, 360.0f, 360.0f)) bResult = false;
		// Check only z rotation
		//	if (!CheckAxisAngle(0.0f, 0.0f, 1.0f,   0.0f,   0.0f)) bResult = false;
		CHECK(CheckAxisAngle(0.0f, 0.0f, 1.0f,  45.0f,  45.0f));
		//	if (!CheckAxisAngle(0.0f, 0.0f, 1.0f, -45.0f,  45.0f)) bResult = false;
		CHECK(CheckAxisAngle(0.0f, 0.0f, 1.0f,  90.0f,  90.0f));
		CHECK(CheckAxisAngle(0.0f, 0.0f, 1.0f, 135.0f, 135.0f));
		CHECK(CheckAxisAngle(0.0f, 0.0f, 1.0f, 180.0f, 180.0f));
		//	if (!CheckAxisAngle(0.0f, 0.0f, 1.0f, 225.0f, 225.0f)) bResult = false;
		//	if (!CheckAxisAngle(0.0f, 0.0f, 1.0f, 270.0f, 270.0f)) bResult = false;
		//	if (!CheckAxisAngle(0.0f, 0.0f, 1.0f, 315.0f, 315.0f)) bResult = false;
		//	if (!CheckAxisAngle(0.0f, 0.0f, 1.0f, 360.0f, 360.0f)) bResult = false;
	}
}