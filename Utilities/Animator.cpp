#include "stdafx.h"
#include "Animator.h"

AnimationClip::AnimationClip(const wstring& clipName, const ScratchImage& srcTex, UINT frameCount, const Vector2& startPos, const Vector2& endPos, bool bReverse, bool bLoop, float playRate)
	: clipName(clipName), frameCount(frameCount), bReverse(bReverse), bLoop(bLoop),playRate(playRate)
{
	float imageWidth = (float)srcTex.GetMetadata().width;
	float imageHeight = (float)srcTex.GetMetadata().height;

	Vector2 clipSize = Vector2(abs(endPos.x - startPos.x), abs(endPos.y - startPos.y));
	//Vector2 frameSize = Vector2()
}