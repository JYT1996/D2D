#pragma once
class Camera
{
	DECLARE_SINGLETON(Camera);

public:
	void Update();
	void Render();

public:
	void UpdateView();
	void UpdateProj();

public:
	Vector2 GetPosition() const { return position; }
	Vector2 UnProject(const Vector2& source);

	void ZoomIn();
	void ZoomOut();
	void InitZoom();

	void SetPosition(const Vector2& position);
	void SetEdges(bool bEdge) { this->bEdge = bEdge; }
	void SetEdges(const Vector2& min, const Vector2& max)
	{
		minEdge = min;
		maxEdge = max;
		bEdge = true;
	}

	void Move(const Vector2& position);

private:
	unique_ptr<class ViewProjectionBuffer> VPBuffer;

	Matrix view, projection;

	Vector3 eye, at, up = { 0, 1, 0 };
	Vector2 position;
	Vector2 LB, RT = { gWinWidth, gWinHeight };
	float widthRatio = gWinWidth / gWinHeight;
	
	Vector2 minEdge, maxEdge;
	bool bEdge = false;

	float speed = 300.0f;
	float zoomSpeed = 400.0f;
};