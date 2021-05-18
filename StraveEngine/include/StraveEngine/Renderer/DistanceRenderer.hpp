#pragma once

#include <StraveEngine/System/Vector2.hpp>
#include <StraveEngine/System/Vector4.hpp>
#include <StraveEngine/System/DataTypes.hpp>

#include <vector>
#include <memory>


#define INIT_RENDER_SECTION_KEY			0
#define	MIN_MAP_SIZE				100.0f
#define MIN_RADIUS				1.0f
#define RENDERING_GRID_DIM			{ 40, 40 }
#define MAX_RENDER_DISTANCE			5000.0f
#define PRELOAD_RENDER_DISTANCE_OFFSET		20.0f	


namespace Strave
{
	class DistanceRendererConstraints;
	class GameObject;

	class DistanceRenderer
	{
	private:
		class Segment;
		typedef int32_t SegmentKey_t;

		class RenderSection
		{
		private:
			typedef std::vector<GameObject*>		OBJVEC;
			typedef std::vector<std::shared_ptr<Segment>>	RNDRGRID;
			typedef std::vector<std::shared_ptr<Segment>>*	RNDRGRID_PTR;

			struct Grid
			{
				inline Grid() : 
					InRange(std::make_shared<RNDRGRID>()),
					NotInRange(std::make_shared<RNDRGRID>())
				{}
				inline ~Grid() {}

				std::shared_ptr<RNDRGRID> InRange;
				std::shared_ptr<RNDRGRID> NotInRange;
			};

			struct RenderBuffer
			{
				inline RenderBuffer() : 
					Preloaded(std::make_shared<OBJVEC>()),
					Loaded(Preloaded)
				{}
				inline ~RenderBuffer() {}

				std::shared_ptr<OBJVEC> Preloaded;
				std::shared_ptr<OBJVEC> Loaded;
			};

			struct RenderArea
			{
				Shapes::Circle RenderArea;
				Shapes::Circle PreloadArea;
			};

		public:
			RenderSection(const DistanceRendererConstraints& constraints, const std::vector<std::shared_ptr<Segment>>& grid);
			~RenderSection() = default;

			inline void SetRenderDistance(float radius) { radius >= MIN_RADIUS ? m_PreloadRenderDistance = radius : 0; }
			inline std::shared_ptr<OBJVEC>& GetObjectsToRender() const { return m_RenderingBuffer->Loaded; }
			inline const Vector2f& GetPointPosition(void) const { return m_RenderingArea.RenderArea.GetPostion(); }
			inline const Vector2f& GetCenterPoint(void) const { return m_RenderingArea.PreloadArea.GetPostion(); }
			inline const float GetRenderDistance(void) const { return m_RenderDistance; };
			inline const std::vector<GameObject*>& GetObjectContainer(const Segment& seg) const { return *seg.m_GO2DReferenceContainer; }

			void Render(Renderer& renderer);	// runtime function
			state_t Update(void);			// runtime function
			state_t OptimizedUpdate(void);		// runtime function
			state_t RawUpdate(void);		// runtime function
			inline void UpdatePointPosition(const Vector2f& pointPosition) { m_RenderingArea.RenderArea.SetPosition(pointPosition); }

		private:
			void Init(const DistanceRendererConstraints& constraints, const std::vector<std::shared_ptr<Segment>>& grid);
			void PreloadRenderingGrid(void);
			float VerifyRadius(float radius) const;
			float GetPreloadRenderOffset(void) const;
			inline void LoadPreloadedBuffer(void) { m_RenderingBuffer->Loaded = m_RenderingBuffer->Preloaded; }

		private:
			float				m_PreloadRenderOffset;
			float				m_PreloadRenderDistance;
			float				m_RenderDistance;
			RNDRGRID_PTR			m_GridReference;
			RenderArea			m_RenderingArea;
			std::shared_ptr<Grid>		m_RenderingGrid;
			std::shared_ptr<RenderBuffer>	m_RenderingBuffer;
		};
		class Segment
		{
		public:
			Segment(SegmentKey_t key, const Vector2f& size, const Vector2f& pos, const std::vector<GameObject*>& go2dSegCon);
			~Segment() = default;

			void ShowContainerContent(void) const;
			inline unsigned int GetContainerSize() { return m_ContainerSize; }
			inline int GetKey(void) const { return m_Key; }
			inline const Vector2f& GetCenterPoint(void) const { return m_CenterPoint; }
			inline const Vector2f& GetSize(void) const { return m_Size; }
			inline const Vector2f& GetPosition(void) const { return m_Position; }
			inline bool IsOccupied(void) const { return m_OccupancyState; };

		private:
			void Init(const std::vector<GameObject*>& go2dSegCon);
			Vector2f InitCenterPoint(const Vector2f& pos, const Vector2f& size) const;
			friend const std::vector<GameObject*>& RenderSection::GetObjectContainer(const Segment& seg) const;

		private:
			bool				m_OccupancyState;
			unsigned int			m_ContainerSize;
			SegmentKey_t			m_Key;
			Vector2f			m_Size;
			Vector2f			m_Position;
			Vector2f			m_CenterPoint;
			std::vector<GameObject*>*	m_GO2DReferenceContainer;
		};

	public:
		DistanceRenderer(const DistanceRendererConstraints& constraints, const std::vector<GameObject*>& go2dCon, const Vector4f& normMapPoints);
		~DistanceRenderer() = default;

		void ShowSegmentContent(void) const;
		static Vector4f GetHighestPoints(const std::vector<GameObject*>& go2dCon);
		inline std::shared_ptr<RenderSection> GetRenderSection(void) { return m_RenderSection; }

	private:
		void Init(const DistanceRendererConstraints& constraints, const std::vector<GameObject*>& go2dCon);
		std::vector<GameObject*>* GetObjectsInSegmentRange(const Vector2f& segPos, const Vector2f& segSize, std::vector<GameObject*>& unassignedObjects);
		void CreateSegments(void);
		Vector2f GetMapSize(void) const;

	private:
		Vector2u				m_NumberOfFields;
		Vector4f				m_NormalizedMapPoints;
		Vector2f				m_MapSize;
		std::vector<std::shared_ptr<Segment>>	m_Grid;
		std::shared_ptr<RenderSection>		m_RenderSection;
		std::vector<GameObject*>*		m_GO2DContainerReference;
	};
}

