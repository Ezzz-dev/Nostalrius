local combat = Combat()
combat:setParameter(COMBAT_PARAM_TYPE, COMBAT_ENERGYDAMAGE)
combat:setParameter(COMBAT_PARAM_EFFECT, CONST_ME_TELEPORT)
combat:setArea(createCombatArea(AREA_SQUAREWAVE5))

function onGetFormulaValues(player, level, maglevel)
	local base = 150
	local variation = 50
	
	local formula = 3 * maglevel + (2 * level)
	
	local min = (formula * (base - variation)) / 100
	local max = (formula * (base + variation)) / 100
	return -min, -max
end

combat:setCallback(CALLBACK_PARAM_LEVELMAGICVALUE, "onGetFormulaValues")

function onCastSpell(creature, variant)
	return combat:execute(creature, variant)
end