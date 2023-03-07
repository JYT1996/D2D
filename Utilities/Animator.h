#pragma once

class AnimationClip
{
public:
	AnimationClip(const wstring& clipName, const ScratchImage& srcTex, UINT frameCount, const Vector2& startPos, const Vector2& endPos, bool bReverse = false, bool bLoop = true, float playRate = 1.0f / 30.0f);

	wstring GetClipName() const { return clipName; }
	Vector2 GetKeyframe(UINT index) const { return keyframes[index]; }
	Vector2 GetTexelFrameSize() const { return texelFrameSize; }
	UINT GetFrameCount() const { return frameCount; }
	UINT GetLastFrameIndex() const { return (UINT)keyframes.size() - 1; }
	bool GetIsReverse() const { return bReverse; }
	bool GetIsLoop() const { return bLoop; }
	float GetPlayRate() { return playRate; }

	void SetLoop(bool bLoop) { this->bLoop = bLoop; }
	void SetPlayRate(float playRate) { this->playRate = playRate; }

private:
	wstring clipName = L"";
	vector<Vector2> keyframes;
	UINT frameCount = 0;

	Vector2 texelFrameSize;

	bool bReverse = false;
	bool bLoop = true;
	float playRate = 1.0f / 30.0f;
};