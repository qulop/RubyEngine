#version 460 core


#stage vertex
    layout(location = 0) in vec3 a_Pos;
    layout(location = 1) in vec3 a_Color;
    layout(location = 2) in vec2 a_TextureCoordinate;
    layout(location = 3) in vec3 a_Normal;


    layout(std140, binding = 0) uniform u_Transform {
        mat4 Model;
        mat4 View;
        mat4 Projection;
        mat3 NormalMatrix;
    };

    layout(location = 0) out vec3 v_FragmentPos;
    layout(location = 1) out vec3 v_Normal;
    layout(location = 2) out vec2 v_TextureCoordinate;
    layout(location = 3) out vec3 v_Color;


    void main() {
        vec4 ViewSpaceVector = View * Model * vec4(a_Pos, 1.0);

        gl_Position = Projection * ViewSpaceVector;
        v_FragmentPos = vec3(ViewSpaceVector);  // In fragment shader we want to have the viewer position in the view space
        v_Normal = NormalMatrix * a_Normal;
        v_TextureCoordinate = a_TextureCoordinate;
        v_Color = a_Color;
    }
#endstage

#stage fragment 
    layout(location = 0) in vec3 v_FragmentPos;
    layout(location = 1) in vec3 v_Normal;
    layout(location = 2) in vec3 v_TextureCoordinate;
    layout(location = 3) in vec3 v_Color;


    layout(std140, binding = 1) uniform u_Light {
        vec3 LightPos;
        vec3 LightColor;
        float SpecularStrength;
    };

    layout(std140, binding = 2) uniform u_Material {
        vec3 AmbientColor;
        vec3 DiffuseColor;
        vec3 SpecularColor;
        float ShininessExponent;
    };


    layout(location = 0) out vec4 FragColor;


    vec3 GetLightDirectionVector() {
        return normalize(LightPos - v_FragmentPos);
    }

    vec3 GetAmbientVector() {
        return AmbientColor * LightColor;
    }

    vec3 GetDiffuseVector() {
        vec3 DiffuseResultVector = max(dot(normalize(v_Normal), GetLightDirectionVector()), 0.0) * DiffuseColor;

        return DiffuseResultVector * LightColor;
    }

    vec3 GetSpecularVector() {
        // Since we're in the view space, the viewer will always be at (0,0,0)
        vec3 ViewDirection = normalize(-v_FragmentPos);
        vec3 ReflectDirection = reflect(-GetLightDirectionVector(), normalize(v_Normal));

        vec3 SpecularResultVector =  pow(max(dot(ViewDirection, ReflectDirection), 0.0), ShininessExponent);

        return SpecularStrength * (SpecularResultVector * SpecularColor) * LightColor;
    }


    void main() {
        vec3 ResultColor = (GetAmbientVector() + GetDiffuseVector() + GetSpecularVector()) * v_Color;
        FragColor = vec4(ResultColor, 1.0);
    }
#endstage