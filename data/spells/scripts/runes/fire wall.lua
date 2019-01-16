local combat = Combat()
combat:setParameter(COMBAT_PARAM_TYPE, COMBAT_FIREDAMAGE)
combat:setParameter(COMBAT_PARAM_DISTANCEEFFECT, CONST_ANI_FIRE)
combat:setParameter(COMBAT_PARAM_MAGICEFFECT, CONST_ME_HITBYFIRE)
combat:setParameter(COMBAT_PARAM_CREATEITEM, 2118)
combat:setArea(createCombatArea(AREA_WALLFIELD, AREADIAGONAL_WALLFIELD))

function onCastSpell(creature, variant, isHotkey)
	return combat:execute(creature, variant)
end