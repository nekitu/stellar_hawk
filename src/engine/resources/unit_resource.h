#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include "types.h"
#include "vec2.h"
#include "color.h"
#include "rect.h"
#include "resource.h"
#include "resources/sprite_resource.h"

namespace engine
{
enum class AutoDeleteType
{
	None,
	OffscreenBoundary, // delete when the unit goes out of the offscreen boundary
	OutOfScreen, // delete when out of screen, any side, used for projectiles
	EndOfScreen // delete when exits screen, depending on screen mode vertical/horizontal
};

struct SpriteInstanceResource
{
	struct SpriteResource* spriteResource = nullptr;
	std::string name;
	std::string animationName = "default";
	Vec2 position;
	Vec2 scale = { 1.0f, 1.0f };
	bool verticalFlip = false;
	bool horizontalFlip = false;
	f32 rotation = 0;
	u32 orderIndex = 0;
	bool collide = true;
	bool visible = true;
	bool shadow = true;
	bool relativeToRoot = true;
	f32 health = 100.0f;
	Color color = Color::black;
	ColorMode colorMode = ColorMode::Add;
	Color hitColor = Color::red;
	struct SpriteResource* hitSprite = nullptr; // spawn a unit on projectile/beam hit
	std::map<std::string /*anim name*/, struct AnimationResource*> animations;
};

struct WeaponInstanceResource
{
	SpriteInstanceResource* attachTo = nullptr;
	struct WeaponResource* weaponResource = nullptr;
	Vec2 localPosition;
	f32 ammo = 100;
	bool active = true;
};

struct ControllerInstanceResource
{
	Json::Value json;
	struct ScriptResource* script = nullptr;
};

struct UnitLifeStage
{
	std::string name;
	f32 triggerOnHealth = 100;
};

enum class UnitType
{
	None,
	Player,
	Enemy,
	Item,
	PlayerProjectile,
	EnemyProjectile,

	Count
};

struct UnitResource : Resource
{
	std::string name;
	UnitType unitType = UnitType::None;
	f32 speed = 10.0f;
	f32 shadowScale = 1.0f;
	bool shadow = false;
	Vec2 shadowOffset;
	bool visible = true;
	AutoDeleteType autoDeleteType = AutoDeleteType::EndOfScreen;
	bool collide = true;
	std::string rootName;
	struct ScriptResource* script = nullptr;
	std::map<std::string /*sprite instance name*/, SpriteInstanceResource*> sprites;
	std::vector<UnitLifeStage*> stages;
	std::map<std::string /*weapon name*/, WeaponInstanceResource*> weapons;
	std::map<std::string /*controller name*/, ControllerInstanceResource> controllers;

	bool load(Json::Value& json) override;
	void unload() override;
};

}
