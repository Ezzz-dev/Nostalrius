local combat = Combat()
combat:setParameter(COMBAT_PARAM_TYPE, COMBAT_ENERGYDAMAGE)
combat:setParameter(COMBAT_PARAM_DISTANCEEFFECT, CONST_ANI_ENERGY)
combat:setParameter(COMBAT_PARAM_MAGICEFFECT, CONST_ME_ENERGYHIT)
combat:setParameter(COMBAT_PARAM_CREATEITEM, 2122)

function onCastSpell(creature, variant, isHotkey)
	return combat:execute(creature, variant)
end