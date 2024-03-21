#include "Transform.fx"
#include "RenderBase.fx"

struct GameEngineVertex2D
{
    float4 POSITION : POSITION;
    float4 TEXCOORD : TEXCOORD;
};


struct PixelOutPut
{
    // �ȼ����̴��� ������ ����
    float4 POSITION : SV_POSITION;
    float4 TEXCOORD : TEXCOORD;
    float4 OLTEXCOORD : OLTEXCOORD;
};


cbuffer SpriteRendererInfo : register(b3)
{
    int FlipLeft = 0;
    int FlipUp = 0;
    float Temp1;
    float Temp2;
};


cbuffer SpriteData : register(b1)
{
    float Pos2DX;
    float Pos2DY;
    float Scale2DX;
    float Scale2DY;
};

cbuffer OverlayInfo : register(b2)
{
    float Intensity;
    float4 OverlayUVPlus;
    float4 OverlayUVMul;
};


PixelOutPut ContentsShader_VS(GameEngineVertex2D _Input)
{
    // _Input 0.5 0.5
    
    // ���̴� ���� ��� 0�� �ڷ������� �ʱ�ȭ �ϴ°�
    PixelOutPut Result = (PixelOutPut) 0;
    
    // ���� ���ϴ� ���� �̾ȿ� �־��ټ� �־�� �Ѵ�.
    
    Result.POSITION = mul(_Input.POSITION, WorldViewProjectionMatrix);    
    
    float4 CalUV = _Input.TEXCOORD;

    CalUV.x *= VertexUVMul.x;
    CalUV.y *= VertexUVMul.y;
    
       
    CalUV.x += VertexUVPlus.x;
    CalUV.y += VertexUVPlus.y;

    
    // ����� ������ ���ִ� ������۰� �ǹ̰� �־�? �׷� ������۴� ���� �˾Ƽ� �����Ҳ�.
    if (0 != FlipLeft)
    {
        CalUV.x *= -1;
        CalUV.x += 1;
    }

    if (0 != FlipUp)
    {
        CalUV.y *= -1;
        CalUV.y += 1;
    }
    
    Result.TEXCOORD.x = (CalUV.x * Scale2DX) + Pos2DX;
    Result.TEXCOORD.y = (CalUV.y * Scale2DY) + Pos2DY;
    
    Result.OLTEXCOORD.x = Result.TEXCOORD.x + OverlayUVPlus.x;
    Result.OLTEXCOORD.y = Result.TEXCOORD.y + OverlayUVPlus.y;
    
    Result.OLTEXCOORD.x *= OverlayUVMul.x;
    Result.OLTEXCOORD.y *= OverlayUVMul.y;
    
    // ���ؽ� ���� ��� �Ǿ��ֳ�?
    return Result;
}

// b���� 14
// t�ؽ�ó 
// s���÷� 
// ���� ������ �������� �ʴ´�.

// ���� ���÷��� �ؽ�ó�� 1������ ���Ǳ� ������
// ���÷��� �ؽ�ó�� ������ �����ö� ������ ���ְų� Ư���� ���ĵ��� ���ο���
// ������ִ� �뵵�� �ִ�.

cbuffer ColorData : register(b1)
{
    float4 PlusColor; // �������� ���Ѵ�.
    float4 MulColor; // �������� ���Ѵ�.
};

Texture2D DiffuseTex : register(t1);
Texture2D OverlayTex : register(t2);
Texture2D MaskTex : register(t3);

SamplerState DiffuseTexSampler : register(s1);
SamplerState OverlayTexSampler : register(s2);

struct PixelOut
{
    float4 Color0 : SV_Target0;
    float4 Color1 : SV_Target1;
    float4 Color2 : SV_Target1;
    float4 Color3 : SV_Target1;
    float4 Color4 : SV_Target1;
    float4 Color5 : SV_Target1;
    float4 Color6 : SV_Target1;
    float4 Color7 : SV_Target1;
};

// SV_Target0
// SV_Target1
// SV_Target2
// SV_Target3
// SV_Target4

PixelOut ContentsShader_PS(PixelOutPut _Input) : SV_Target0
{
    PixelOut Result = (PixelOut) 0.0f;
    
    float4 Color = DiffuseTex.Sample(DiffuseTexSampler, _Input.TEXCOORD.xy);
    // �������� �۾��� ����� �Ѵ�.
    
    float4 OverlayColor = OverlayTex.Sample(OverlayTexSampler, _Input.OLTEXCOORD.xy);
    //OverlayColor.a = 0.5f;
    
    int2 ScreenPos = int2(_Input.POSITION.x, _Input.POSITION.y);
    
    // ScreenPos

    // 1280 720 MaskScreenScale;
    // Half ������ MaskScreenScale / 2
    // 256 256 RenderScreenScale;
    
    // BaseScreenPos // ������ ��ġ.
    
    // ScreenPos -= BaseScreenPos;

    
    
    if (MaskMode == 1)
    {
        ScreenPos.x = ScreenPos.x - RendererScreenPos.x;
        ScreenPos.y = ScreenPos.y - RendererScreenPos.y;
        
        ScreenPos.x += MaskScreenScale.x * 0.5f;
        ScreenPos.y += MaskScreenScale.y * 0.5f;
        
        ScreenPos.x -= MaskPivot.x;
        ScreenPos.y += MaskPivot.y;
    }
    
    if (IsMask == 1 && MaskTex[ScreenPos].r <= 0.0f)
    {
        clip(-1);
    }
    
    if (0.0f >= Color.a)
    {
        clip(-1);
    }
    
    if (BaseColorOnly != 0)
    {
        Color = BaseColor;
        Color.a = 1;
    }
        
    Color += PlusColor;
    Color *= MulColor;
    
    Color *= (OverlayColor * Intensity);
    
    if (0 < Target0)
    {
        Result.Color0 = Color;
    }
    if (0 < Target1)
    {
        Result.Color1 = Color;
    }
    if (0 < Target2)
    {
        Result.Color2 = Color;
    }
    if (0 < Target3)
    {
        Result.Color3 = Color;
    }
    
    return Result;
}