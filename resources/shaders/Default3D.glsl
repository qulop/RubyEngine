#version 460 core


#stage vertex
    layout(location = 0) in vec3 a_Pos;
    layout(location = 1) in vec3 a_Color;
    layout(location = 2) in vec2 a_TextureCoordinate;
    layout(location = 3) in vec3 a_Normal;


    layout(location = 0, std140) uniform u_Transform {
        mat4 Model;
        mat4 View;
        mat4 Projection;
        mat3 NormalMatrix;
    };

    layout(location = 0) out vec3 v_FragmentPos;
    layout(location = 1) out vec3 v_Normal;
    layout(location = 2) out vec3 v_TextureCoordinate;
    layout(location = 3) out vec3 v_Color;


    void main() {
        gl_Position = Projection * View * Model * vec4(a_Pos, 1.0);
        v_FragmentPos = vec3(Model * vec4(a_Pos, 1.0));
        v_Normal = NormalMatrix * a_Normal;
        v_TextureCoordinate = a_TextureCoordinate;
        v_Color = a_Color;
    }
#endstage

#stage fragment 
    layout(location = 0) out vec3 v_FragmentPos;
    layout(location = 1) out vec3 v_Normal;
    layout(location = 2) out vec3 v_TextureCoordinate;
    layout(location = 3) out vec3 v_Color;


    layout(location = 0) uniform u_Light {
        vec3 LightPos;
        vec3 LightColor;
        float LightAmbientStrength;
    };

    layout(location = 1) uniform u_Specular {
        vec3 ViewerPos;
        float SpecularStrength;
        float ShininessExponent;
    }


    layout(location = 0) out vec4 FragCoord;


    vec3 GetLightDirectionVector() {
        return normalize(LightPos - v_FragmentPos);
    }

    vec3 GetAmbientVector() {
        return LightAmbientStrength * LightColor;
    }

    vec3 GetDiffuseVector() {
        return max(dot(normalize(v_Normal), GetLightDirectionVector()), 0.0) * LightColor;
    }

    vec3 GetSpecularVector() {
        vec3 ViewDirection = normalize(ViewerPos - v_FragmentPos);
        vec3 ReflectDirection = reflect(-GetLightDirection(), normalize(v_Normal));

        return SpecularStrength * pow(max(dot(ViewDirection, ReflectDirection), 0.0), ShininessExponent) * LightColor;
    }


    void main() {
        vec3 ResultColor = (GetAmbientVector() + GetDiffuseVector() + GetSpecularVector()) * v_Color;
        FragCoord = vec4(ResultColor, 1.0);
    }
#endstage