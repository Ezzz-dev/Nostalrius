local combat = Combat()
combat:setParameter(COMBAT_PARAM_TYPE, COMBAT_EARTHDAMAGE)
combat:setParameter(COMBAT_PARAM_EFFECT, CONST_ME_HITBYPOISON)
combat:setParameter(COMBAT_PARAM_DISTANCEEFFECT, CONST_ANI_ENERGY)

function onTargetCreature(creature, target)
	local player = Player(creature)
	
	local condition = Condition(CONDITION_POISON)
	condition:setTiming(computeFormula(player:getLevel(), player:getMagicLevel(), 70, 20))
	target:addCondition(condition)
end

combat:setCallback(CALLBACK_PARAM_TARGETCREATURE, "onTargetCreature")

function onCastSpell(creature, variant)
	return combat:execute(creature, variant)
end