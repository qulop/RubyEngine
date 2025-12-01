#pragma once

#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>

#include <math/vec/Vec4.hpp>
#include <math/vec/Vec3.hpp>
#include <math/CommonFunc.hpp>
#include <math/simd/SIMD.hpp>



namespace Kiwi {
    class Mat4 {
    public:
        using value_type = f32;
        using ValueType = f32;

        using ColumnType = Vec4;
        using column_type = Vec4;

    public:
        static constexpr size_t Size() noexcept {
            return 4;
        }

        static constexpr Mat4 Identity() noexcept {
            return Mat4(1.f);
        }

    public:
        constexpr Mat4() :
            m_matrix{ {}, {}, {}, {} }
        {}

        constexpr explicit Mat4(f32 scalar) :
            m_matrix{
                ColumnType(scalar, 0.f, 0.f, 0.f),
                ColumnType(0.f, scalar, 0.f, 0.f),
                ColumnType(0.f, 0.f, scalar, 0.f),
                ColumnType(0.f, 0.f, 0.f, scalar)
            }
        {}

        constexpr Mat4(const glm::mat4 &mat) {
            m_matrix[0] = mat[0];
            m_matrix[1] = mat[1];
            m_matrix[2] = mat[2];
            m_matrix[3] = mat[3];
        }

        constexpr Mat4(glm::mat4 &&mat) noexcept {
            m_matrix[0] = std::exchange(mat[0], glm::vec4(0));
            m_matrix[1] = std::exchange(mat[1], glm::vec4(0));
            m_matrix[2] = std::exchange(mat[2], glm::vec4(0));
            m_matrix[3] = std::exchange(mat[3], glm::vec4(0));
        }

        constexpr Mat4(const ColumnType& c0, const ColumnType& c1, const ColumnType& c2, const ColumnType& c3) :
            m_matrix{ c0, c1, c2, c3 }
        {}

        constexpr Mat4(
            f32 v00, f32 v01, f32 v02, f32 v03,
            f32 v10, f32 v11, f32 v12, f32 v13,
            f32 v20, f32 v21, f32 v22, f32 v23,
            f32 v30, f32 v31, f32 v32, f32 v33
        ) :
            Mat4(
                ColumnType{ v00, v01, v02, v03 },
                ColumnType{ v10, v11, v12, v13 },
                ColumnType{ v20, v21, v22, v23 },
                ColumnType{ v30, v31, v32, v33 }
            )
        {}


        constexpr Mat4(const Mat4& other) = default;

    public:
        constexpr const ColumnType& operator[](u32 column) const {
            KIWI_ASSERT(column < 4, "Out of bounds");

            return m_matrix[column];
        }

        constexpr ColumnType & operator[](u32 column) {
            KIWI_ASSERT(column < 4, "Out of bounds");

            return m_matrix[column];
        }

        KIWI_NODISCARD constexpr Mat4 operator*(const Mat4& b) const {
            using MySplatX = SplatX<4, f32, GetGlobalVectorizationMode()>;
            using MySplatY = SplatY<4, f32, GetGlobalVectorizationMode()>;
            using MySplatZ = SplatZ<4, f32, GetGlobalVectorizationMode()>;
            using MySplatW = SplatW<4, f32, GetGlobalVectorizationMode()>;


            ColumnType aRow0 = m_matrix[0];
            ColumnType aRow1 = m_matrix[1];
            ColumnType aRow2 = m_matrix[2];
            ColumnType aRow3 = m_matrix[3];

            ColumnType bRow0 = b[0];
            ColumnType bRow1 = b[1];
            ColumnType bRow2 = b[2];
            ColumnType bRow3 = b[3];

            ColumnType resRow0 = (MySplatX::Call(aRow0) * bRow0) + (MySplatY::Call(aRow0) * bRow1) + (MySplatZ::Call(aRow0) * bRow2) + (MySplatW::Call(aRow0) * bRow3);
            ColumnType resRow1 = (MySplatX::Call(aRow1) * bRow0) + (MySplatY::Call(aRow1) * bRow1) + (MySplatZ::Call(aRow1) * bRow2) + (MySplatW::Call(aRow1) * bRow3);
            ColumnType resRow2 = (MySplatX::Call(aRow2) * bRow0) + (MySplatY::Call(aRow2) * bRow1) + (MySplatZ::Call(aRow2) * bRow2) + (MySplatW::Call(aRow2) * bRow3);
            ColumnType resRow3 = (MySplatX::Call(aRow3) * bRow0) + (MySplatY::Call(aRow3) * bRow1) + (MySplatZ::Call(aRow3) * bRow2) + (MySplatW::Call(aRow3) * bRow3);

            return Mat4(resRow0, resRow1, resRow2, resRow3);
        }

        constexpr Mat4& operator*=(const Mat4& b) {
            return (*this = *this * b);
        }

        constexpr bool operator==(const glm::mat4& other) const noexcept {
            return (m_matrix[0] == other[0]) && (m_matrix[1] == other[1]) &&
                (m_matrix[2] == other[2]) && (m_matrix[3] == other[3]);
        }

    public:
        KIWI_NODISCARD constexpr Mat4 Translate(const Vec3& v) const noexcept {
            Mat4 res{ *this };
            res[3] = (m_matrix[0] * v[0]) + (m_matrix[1] * v[1]) + (m_matrix[2] * v[2]) + m_matrix[3];

            return res;
        }

        constexpr Mat4& TranslateSelf(const Vec3& v) noexcept {
            return (*this = this->Translate(v));
        }

        KIWI_NODISCARD constexpr Mat4 Scale(const Vec3& v) const noexcept {
            Mat4 res;
            res[0] = m_matrix[0] * v[0];
            res[1] = m_matrix[1] * v[1];
            res[2] = m_matrix[2] * v[2];
            res[3] = m_matrix[3];

            return res;
        }

        constexpr Mat4& ScaleSelf(const Vec3& v) noexcept {
            return (*this = this->Scale(v));
        }

    private:
        ColumnType m_matrix[4];
    };
}
