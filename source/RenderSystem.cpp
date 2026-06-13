#include"GameSystem.h"
void GameSystem::Render::Update()
{
	EntityManager& em = EntityManager::GetInstance();
	for (auto& e : em.GetEntity(EntityType::BACK_GROUND))
	{
		auto r = e->Get<Renderer>();
		auto pos = e->Get<Transformer>()->GetPos();
		auto rect = e->Get<Collider>()->GetHitBox().GetRect();
		auto img = e->Get<Imager>();
		r->SetDstRect({ (pos.x - g_pos.x / 15.0f) * scale,(pos.y - g_pos.y / 15.0f) * scale,rect.w * scale,rect.h * scale })
			->SetDelay(3)
			->SetTexture(img->GetTexture())
			->Update();
	}
	for (auto& e : em.GetEntity(EntityType::PLAYER))
	{
		auto r = e->Get<Renderer>();
		auto pos = e->Get<Transformer>()->GetPos();
		auto rect = e->Get<Collider>()->GetHitBox().GetRect();
		auto img = e->Get<Imager>();
		r->SetDstRect({ (pos.x - g_pos.x) * scale,(pos.y - g_pos.y) * scale,rect.w * scale,rect.h * scale })
			->SetDelay(3)
			->SetTexture(img->GetTexture())
			->Update();
	}
	for (auto& e : em.GetEntity(EntityType::NORMAL_ENERMY))
	{
		auto r = e->Get<Renderer>();
		auto pos = e->Get<Transformer>()->GetPos();
		auto rect = e->Get<Collider>()->GetHitBox().GetRect();
		auto img = e->Get<Imager>();
		r->SetDstRect({ (pos.x - g_pos.x) * scale,(pos.y - g_pos.y) * scale,rect.w * scale,rect.h * scale })
			->SetDelay(3)
			->SetTexture(img->GetTexture())
			->Update();
	}
	for (auto& e : em.GetEntity(EntityType::EQUIPMENT))
	{
		if (e->GetState() != EntityState::LOOTED)
		{
			auto r = e->Get<RendererWithAngle>();
			auto pos = e->Get<TransformerWithAngle>()->GetPos();
			auto rect = e->Get<Collider>()->GetHitBox().GetRect();
			auto img = e->Get<Imager>();
			r->SetDstRect({ (pos.x - g_pos.x) * scale,(pos.y - g_pos.y) * scale,rect.w * scale,rect.h * scale })
				->SetDelay(3)
				->SetTexture(img->GetTexture());
			r->SetAngle(e->Get<TransformerWithAngle>()->GetAngle())
				->SetCenter({ 25.0f * scale,25.0f * scale })
				->Update();
		}
	}
	for (auto& e : em.GetEntity(EntityType::BULLET))
	{
		auto r = e->Get<RendererWithAngle>();
		auto pos = e->Get<TransformerWithAngle>()->GetPos();
		auto rect = e->Get<Collider>()->GetHitBox().GetRect();
		auto img = e->Get<Imager>();
		r->SetDstRect({ (pos.x - g_pos.x) * scale,(pos.y - g_pos.y) * scale,rect.w * scale,rect.h * scale })
			->SetDelay(3)
			->SetTexture(img->GetTexture())
			->Update();
		r->SetAngle(e->Get<TransformerWithAngle>()->GetAngle())
			->SetCenter({ rect.w / 2.0f * scale,rect.h / 2.0f * scale })
			->Update();
	}
	for (auto& e : em.GetEntity(EntityType::DEAD_EFFECT))
	{
		auto r = e->Get<Renderer>();
		auto pos = e->Get<Transformer>()->GetPos();
		auto rect = e->Get<Collider>()->GetHitBox().GetRect();
		auto img = e->Get<Imager>();
		r->SetDstRect({ (pos.x - g_pos.x) * scale,(pos.y - g_pos.y) * scale,rect.w * scale,rect.h * scale })
			->SetDelay(3)
			->SetTexture(img->GetTexture())
			->Update();
	}
	for (auto& e : em.GetEntity(EntityType::GROUND))
	{
		auto r = e->Get<Renderer>();
		auto pos = e->Get<Transformer>()->GetPos();
		auto rect = e->Get<Collider>()->GetHitBox().GetRect();
		auto img = e->Get<Imager>();
		r->SetDstRect({ (pos.x - g_pos.x) * scale,(pos.y - g_pos.y) * scale,rect.w * scale,rect.h * 2.0f * scale })
			->SetDelay(3)
			->SetTexture(img->GetTexture())
			->Update();
	}
	//UI
	for (auto& e : em.GetEntity(EntityType::BUTTON_UI))
	{
		auto r = e->Get<TextRenderer>();
		auto pos = e->Get<TextTransformer>()->GetPos();

		auto rect = e->Get<Collider>()->GetHitBox().GetRect();
		auto img = e->Get<Imager>();
		r->SetDstRect({rect.GetLeft(),rect.GetTop(),rect.w,rect.h})
			->SetTexture(img->GetTexture());
		r->SetText(e->Get<Text>()->GetTTFText())
			->SetTextPos(e->Get<TextTransformer>()->GetTextPos())
			->Update();
	}
}