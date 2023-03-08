#include "stdafx.h"
#include "Animator.h"

AnimationClip::AnimationClip(const wstring& clipName, const ScratchImage& srcTex, UINT frameCount, const Vector2& startPos, const Vector2& endPos, bool bReverse, bool bLoop, float playRate)
	: clipName(clipName), frameCount(frameCount), bReverse(bReverse), bLoop(bLoop), playRate(playRate)
{
	float imageWidth = (float)srcTex.GetMetadata().width;
	float imageHeight = (float)srcTex.GetMetadata().height;

	Vector2 clipSize = Vector2(abs(endPos.x - startPos.x), abs(endPos.y - startPos.y));
	Vector2 frameSize = Vector2(clipSize.x / frameCount, clipSize.y);

	Vector2 texelSize = Vector2(1.0f / imageWidth, 1.0f / imageHeight);
	Vector2 texelStartPos = startPos * texelSize;
	texelFrameSize = frameSize * texelSize;

	for (UINT i = 0; i < frameCount; ++i)
	{
		Vector2 keyframe;
		keyframe.x = texelStartPos.x + texelFrameSize.x * i;
		keyframe.y = texelStartPos.y;
		keyframes.push_back(keyframe);
	}
}

Animator::Animator(const shared_ptr<AnimationClip>& animClip)
	: currentAnimClip(animClip)
{
	animClips.emplace(animClip->GetClipName(), animClip);
}

Animator::Animator(const vector<shared_ptr<AnimationClip>>& animClips)
	: currentAnimClip(animClips[0])
{
	for (const auto& animClip : animClips)
		this->animClips.emplace(animClip->GetClipName(), animClip);
}

void Animator::Update()
{
	if (bStop) return;

	if (deltaTime > currentAnimClip->GetPlayRate())
	{
		if (currentAnimClip->GetIsReverse() == false)
		{
			++currentFrameIndex;

			if (currentFrameIndex >= currentAnimClip->GetFrameCount())
			{
				if (currentAnimClip->GetIsLoop())
					currentFrameIndex = 0;
				else
					currentFrameIndex = currentAnimClip->GetLastFrameIndex();
			}

			currentFrame = currentAnimClip->GetKeyframe(currentFrameIndex);
		}
		else
		{
			if (currentFrameIndex != 0)
				--currentFrameIndex;
			
			currentFrame = currentAnimClip->GetKeyframe(currentFrameIndex);

			if (currentFrameIndex <= 0)
			{
				if (currentAnimClip->GetIsLoop())
					currentFrameIndex = currentAnimClip->GetLastFrameIndex() + 1;
				else
					currentFrameIndex = 0;
			}
		}

		deltaTime = 0;
	}

	deltaTime += TIME->GetDeltaTime();
}

void Animator::AddAnimClip(const shared_ptr<AnimationClip>& animClip)
{
	animClips.emplace(animClip->GetClipName(), animClip);
}

void Animator::SetCurrentAnimClip(const wstring& clipName)
{
	if (animClips.find(clipName) != animClips.end())
	{

	}
}
