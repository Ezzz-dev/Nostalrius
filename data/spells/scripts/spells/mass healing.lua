local combat = Combat()
combat:setParameter(COMBAT_PARAM_EFFECT, CONST_ME_MAGIC_BLUE)
combat:setParameter(COMBAT_PARAM_DISPEL, CONDITION_PARALYZE)
combat:setParameter(COMBAT_PARAM_AGGRESSIVE, false)
combat:setArea(createCombatArea(AREA_CIRCLE3X3))

local healMonsters = true

function onTargetCreature(creature, target)
	if not healMonsters then
		local master = target:getMaster()
		if target:isMonster() and not master or master and master:isMonster() then
			return true
		end
	end
	
	local player = creature:getPlayer()
	
	local base = 200
	local variation = 40
	
	local value = math.random(-variation, variation) + base
	local formula = 3 * player:getMagicLevel() + (2 * player:getLevel())
	if formula >= 101 then
		formula = 100
	end
	local total = formula * value / 100

	doTargetCombatHealth(0, target, COMBAT_HEALING, total, total, CONST_ME_NONE)
	return true
end

combat:setCallback(CALLBACK_PARAM_TARGETCREATURE, "onTargetCreature")

function onCastSpell(creature, variant)
	return combat:execute(creature, variant)
end