local combat = Combat()
combat:setParameter(COMBAT_PARAM_TYPE, COMBAT_FIREDAMAGE)
combat:setParameter(COMBAT_PARAM_EFFECT, CONST_ME_HITBYFIRE)
combat:setParameter(COMBAT_PARAM_DISTANCEEFFECT, CONST_ANI_FIRE)

function onTargetCreature(creature, target)
	local player = Player(creature)
	
	local condition = Condition(CONDITION_FIRE)
	condition:setTiming(computeFormula(player:getLevel(), player:getMagicLevel(), 120, 20))
	target:addCondition(condition)
end

combat:setCallback(CALLBACK_PARAM_TARGETCREATURE, "onTargetCreature")

function onCastSpell(creature, variant)
	return combat:execute(creature, variant)
end