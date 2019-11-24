#include "Renderer.h"
#include "sGameObject.h"
#include "sGameObjectDisplay.h"
#include "Geometry.h"


Renderer::Renderer(sGameObject * object, SDL_Renderer * renderer)
{
	m_object = object;
	m_renderer = renderer;	
}

Renderer::~Renderer()
{
}

void Renderer::render()
{
	if (m_object)
	{
		/*SDL_RenderCopyEx(SDL_Renderer*          renderer,
			SDL_Texture*           texture,
			const SDL_Rect*        srcrect,
			const SDL_Rect*        dstrect,
			const double           angle,
			const SDL_Point*       center,
			const SDL_RendererFlip flip)*/
		SDL_RenderCopy(m_renderer, m_object->GetObjectDisplay()->GetTexture(),
			NULL, &m_object->GetGeometry()->m_rect);
		SDL_RenderPresent(m_renderer);
	}
}
