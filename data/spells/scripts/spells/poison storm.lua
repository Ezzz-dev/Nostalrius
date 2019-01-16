local combat = Combat()
combat:setParameter(COMBAT_PARAM_TYPE, COMBAT_EARTHDAMAGE)
combat:setParameter(COMBAT_PARAM_EFFECT, CONST_ME_GREEN_RINGS)
combat:setArea(createCombatArea(AREA_CIRCLE5X5))

function onTargetCreature(creature, target)
	local player = Player(creature)
	
	local condition = Condition(CONDITION_POISON)
	condition:setTiming(computeFormula(player:getLevel(), player:getMagicLevel(), 200, 50))
	target:addCondition(condition)
end

combat:setCallback(CALLBACK_PARAM_TARGETCREATURE, "onTargetCreature")

function onCastSpell(creature, variant)
	return combat:execute(creature, variant)
end