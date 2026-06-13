#include"GameSystem.h"

//Player
void GameSystem::Spawn::Player(const Vec2d<float>& pos, SDL_Renderer* renderer)
{
	EntityManager& em = EntityManager::GetInstance();
	auto player = em.AddEntity(EntityType::PLAYER);
	player->Add<Controller>()
		->Add<Transformer>()
		->Add<Renderer>()
		->Add<Physics>()
		->Add<Collider>()
		->Add<Equipments>()
		->Add<Imager>();
	//transform

	auto t = player->Get<Transformer>();
	t->SetPos(pos);
	//physic
	auto player_p = player->Get<Physics>();
	player_p->Add<Gravity>()
		->Add<Drag>()
		->Add<Movement>()
		->Add<Reaction>();
	player_p->SetMaxF({ 10.0,20.0 });
	//collide
	player->Get<Collider>()->GetHitBox().SetRect(t->GetPos().x, t->GetPos().y, PlayerSize.x, PlayerSize.y);
	//image
	TextureManager& tm = TextureManager::GetInstance();
	player->Get<Imager>()->SetTexture(&tm.GetTexture(player->GetType(), TextureType::NONE));
	//render 
	auto r = player->Get<Renderer>();
	r->SetRenderer(renderer);
}
//Normal Enermy
void GameSystem::Spawn::NormalEnermy(const Vec2d<float>& pos, SDL_Renderer* renderer)
{
	EntityManager& em = EntityManager::GetInstance();
	auto enermy = em.AddEntity(EntityType::NORMAL_ENERMY);
	enermy->Add<AutoControl>()
		->Add<Transformer>()
		->Add<Renderer>()
		->Add<Physics>()
		->Add<Collider>()
		->Add<Imager>();
	auto t = enermy->Get<Transformer>();
	t->SetPos(pos);
	auto col = enermy->Get<Collider>()->GetHitBox().SetRect(t->GetPos().x, t->GetPos().y, EnermySize.x, EnermySize.y);
	auto p = enermy->Get<Physics>();
	p->Add<Gravity>()
		->Add<Drag>()
		->Add<Movement>()
		->Add<Reaction>();
	p->SetMaxF({ 10.0,20.0 });
	//collide
	auto r = enermy->Get<Renderer>();
	r->SetRenderer(renderer);
	TextureManager& tm = TextureManager::GetInstance();
	enermy->Get<Imager>()->SetTexture(&tm.GetTexture(enermy->GetType(), TextureType::NONE));
}
//Ground
void GameSystem::Spawn::Ground(const Vec2d<float>& pos, SDL_Renderer* renderer)
{
	EntityManager& em = EntityManager::GetInstance();
	auto ground = em.AddEntity(EntityType::GROUND);
	ground->Add<Transformer>()
		->Add<Imager>()
		->Add<Collider>()
		->Add<Renderer>();
	auto t = ground->Get<Transformer>();
	t->SetPos(pos);
	auto img = ground->Get<Imager>();
	TextureManager& tm = TextureManager::GetInstance();
	img->SetTexture(&tm.GetTexture(ground->GetType(), TextureType::NONE));
	auto col = ground->Get<Collider>();
	col->GetHitBox().SetRect(pos.x, pos.y, GroundSize.x, GroundSize.y);
	auto r = ground->Get<Renderer>();
	r->SetRenderer(renderer);
}
//BackGround
void GameSystem::Spawn::BackGround(const Vec2d<float>& pos, SDL_Renderer* renderer)
{
	EntityManager& em = EntityManager::GetInstance();
	auto ground = em.AddEntity(EntityType::BACK_GROUND);
	ground->Add<Transformer>()
		->Add<Imager>()
		->Add<Collider>()
		->Add<Renderer>();
	auto t = ground->Get<Transformer>();
	t->SetPos(pos);
	auto img = ground->Get<Imager>();
	TextureManager& tm = TextureManager::GetInstance();
	img->SetTexture(&tm.GetTexture(ground->GetType(), TextureType::NONE));
	auto col = ground->Get<Collider>();
	col->GetHitBox().SetRect(0, 0, WIDTH * 12.0f, HEIGHT * 8.0f);
	auto r = ground->Get<Renderer>();
	r->SetRenderer(renderer);
}
//Dead Effect
void GameSystem::Spawn::DeadEffect(EntityType type, const Vec2d<float>& mid_pos, SDL_Renderer* renderer)
{
	EntityManager& em = EntityManager::GetInstance();
	auto& de = em.AddEntity(EntityType::DEAD_EFFECT);
	de->Add<Transformer>()
		->Add<Collider>()
		->Add<Imager>()
		->Add<Renderer>();

	auto de_t = de->Get<Transformer>();
	auto de_col = de->Get<Collider>();
	de_col->GetHitBox().SetRect(de_t->GetPos().x, de_t->GetPos().y, DeadEffectSize.x, DeadEffectSize.y);

	de_t->SetPos(mid_pos - Vec2d<float>{de_col->GetHitBox().GetRect().w / 2.0f, de_col->GetHitBox().GetRect().h / 2.0f});
	TextureManager& tm = TextureManager::GetInstance();

	de->Get<Imager>()->SetTexture(&tm.GetTexture(type, TextureType::DEAD));
	de->Get<Renderer>()->SetRenderer(renderer)->SetDelay(3);
}
//Laser Gun
void GameSystem::Spawn::LaserGun(const Vec2d<float>& pos, SDL_Renderer* renderer)
{
	EntityManager& em = EntityManager::GetInstance();
	auto& equipment = em.AddEntity(EntityType::EQUIPMENT);
	equipment->SetState(EntityState::NONE);
	equipment->Add<TransformerWithAngle>()
		->Add<EquipmentAttrib>()
		->Add<Collider>()
		->Add<Imager>()
		->Add<RendererWithAngle>();
	equipment->Get<TransformerWithAngle>()->SetPos(pos)->SetAngle(0.0f);
	equipment->Get<EquipmentAttrib>()->SetEquipmentType(EntityType::LASER_GUN)->SetBulletType(EntityType::LASER_BULLET);
	equipment->Get<Collider>()->GetHitBox().SetRect(pos.x, pos.y, EquipSize.x, EquipSize.y);
	TextureManager& tm = TextureManager::GetInstance();
	equipment->Get<Imager>()->SetTexture(&tm.GetTexture(equipment->Get<EquipmentAttrib>()->GetEquipmentType(), TextureType::NONE));
	equipment->Get<RendererWithAngle>()->SetRenderer(renderer)->SetDelay(3);
}
//Rocket Gun
void GameSystem::Spawn::RocketGun(const Vec2d<float>& pos, SDL_Renderer* renderer)
{
	EntityManager& em = EntityManager::GetInstance();
	auto& equipment = em.AddEntity(EntityType::EQUIPMENT);
	equipment->SetState(EntityState::NONE);
	equipment->Add<TransformerWithAngle>()
		->Add<EquipmentAttrib>()
		->Add<Collider>()
		->Add<Imager>()
		->Add<RendererWithAngle>();
	equipment->Get<TransformerWithAngle>()->SetPos(pos)->SetAngle(0.0f);
	equipment->Get<EquipmentAttrib>()->SetEquipmentType(EntityType::ROCKET_GUN)->SetBulletType(EntityType::ROCKET_BULLET);
	equipment->Get<Collider>()->GetHitBox().SetRect(pos.x, pos.y, EquipSize.x, EquipSize.y);
	TextureManager& tm = TextureManager::GetInstance();
	equipment->Get<Imager>()->SetTexture(&tm.GetTexture(equipment->Get<EquipmentAttrib>()->GetEquipmentType(), TextureType::NONE));
	equipment->Get<RendererWithAngle>()->SetRenderer(renderer)->SetDelay(3);
}	  
//Rocket Bullet
void GameSystem::Spawn::RocketBullet(const Vec2d<float>& mid_pos, SDL_Renderer* renderer, const Vec2d<float>& veclocity)
{
	EntityManager& em = EntityManager::GetInstance();
	auto bullet = em.AddEntity(EntityType::BULLET);
	bullet->Add<Collider>()
		->Add<TransformerWithAngle>()
		->Add<RendererWithAngle>()
		->Add<Imager>()
		->Add<Physics>()
		->Add<BulletAttrib>()
		->Add<BulletController>();

	auto t = bullet->Get<TransformerWithAngle>();
	t->SetAngle(GetAngle(veclocity));
	auto hb = bullet->Get<Collider>()->GetHitBox().SetRect(mid_pos.x, mid_pos.y, RocketBulletSize.x, RocketBulletSize.y);
	t->SetPos(mid_pos - Vec2d<float>{hb->GetRect().w / 2.0f, hb->GetRect().h / 2.0f});
	bullet->Get<Collider>()->GetHitBox().SetRect(t->GetPos().x, t->GetPos().y, hb->GetRect().w, hb->GetRect().h);
	auto r = bullet->Get<RendererWithAngle>();
	r->SetRenderer(renderer);
	r->SetAngle(t->GetAngle());
	r->SetCenter(Vec2d<float>{hb->GetRect().w / 2.0f, hb->GetRect().h / 2.0f}*scale);
	bullet->Get<BulletController>()->SetVelocity(veclocity);
	auto p = bullet->Get<Physics>();
	auto c = bullet->Get<BulletController>();
	p->IncreaseForce(c->GetVelocity() * 30);
	bullet->Get<BulletAttrib>()->SetBulletType(EntityType::ROCKET_BULLET);
	p->Add<Gravity>();
	p->Get<Gravity>()->SetAcceleration(0.3);
	TextureManager& tm = TextureManager::GetInstance();
	bullet->Get<Imager>()->SetTexture(&tm.GetTexture(bullet->Get<BulletAttrib>()->GetBulletType(), TextureType::NONE));
}
void GameSystem::Spawn::ButtonUI(const Vec2d<float>& pos,const char* text,float f, SDL_Renderer* renderer,TTF_TextEngine* te)
{
	EntityManager& em = EntityManager::GetInstance();
	auto button = em.AddEntity(EntityType::BUTTON_UI)->Add<TextTransformer>()
		->Add<Text>()
		->Add<Collider>()
		->Add<Imager>()
		->Add<TextRenderer>();
	auto tex = button->Get<Text>()->SetTextEngine(te)->SetFont("C:\\Windows\\Fonts\\arial.ttf", f)->SetText(text)->SetColor(255, 0, 0, 255);
	int w, h;
	tex->GetTextSize(&w, &h);
	auto& hb = button->Get<Collider>()->GetHitBox();
		hb.SetRect(pos.x, pos.y, w*1.2f, h*1.2f);
	TextureManager& tm = TextureManager::GetInstance();
	button->Get<Imager>()->SetTexture(&tm.GetTexture(button->GetType(), TextureType::NONE));
	const Vec2d<float> mid_pos = hb.GetRect().GetMidPos();
	const Vec2d<float> text_pos = mid_pos - Vec2d<float>{w/2.0f,h/2.0f};
	button->Get<TextTransformer>()->SetTextPos(text_pos)->SetPos(pos);
	button->Get<TextRenderer>()->SetText(tex->GetTTFText())->SetRenderer(renderer);
}
//Laser Bullet
void GameSystem::Spawn::LaserBullet(const Vec2d<float>& mid_pos, SDL_Renderer* renderer, const Vec2d<float>& velocity)
{
	EntityManager& em = EntityManager::GetInstance();
	auto bullet = em.AddEntity(EntityType::BULLET);
	bullet->Add<Collider>()
		->Add<TransformerWithAngle>()
		->Add<RendererWithAngle>()
		->Add<Imager>()
		->Add<Physics>()
		->Add<BulletAttrib>()
		->Add<BulletController>();

	auto t = bullet->Get<TransformerWithAngle>();
	auto hb = bullet->Get<Collider>()->GetHitBox().SetRect(mid_pos.x, mid_pos.y, LaserBulletSize.x, LaserBulletSize.y);
	t->SetPos(mid_pos - Vec2d<float>{hb->GetRect().w / 2.0f, hb->GetRect().h / 2.0f});
	bullet->Get<Collider>()->GetHitBox().SetRect(t->GetPos().x, t->GetPos().y, hb->GetRect().w, hb->GetRect().h);
	auto r = bullet->Get<RendererWithAngle>();
	r->SetRenderer(renderer);
	r->SetCenter(hb->GetRect().GetMidPos());
	bullet->Get<BulletController>()->SetVelocity(velocity);
	auto p = bullet->Get<Physics>();
	auto c = bullet->Get<BulletController>();
	p->IncreaseForce(c->GetVelocity() * 50);
	bullet->Get<BulletAttrib>()->SetBulletType(EntityType::LASER_BULLET);
	//p->Add<Gravity>();
	//p->Get<Gravity>()->SetAcceleration(0.3);
	TextureManager& tm = TextureManager::GetInstance();
	bullet->Get<Imager>()->SetTexture(&tm.GetTexture(bullet->Get<BulletAttrib>()->GetBulletType(), TextureType::NONE));
}
