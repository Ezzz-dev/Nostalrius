function onStepIn(creature, item, position, fromPosition)
	local tile = Tile(position)
	if tile:hasFlag(TILESTATE_PROTECTIONZONE) then
		return
	end
	
	if item:getId() == 2145 then
		item:transform(2146, 1)
		item:decay()
		doTargetCombatHealth(0, creature, COMBAT_PHYSICALDAMAGE, -60, -60)
	elseif item:getId() == 2146 or item:getId() == 2148 then
		doTargetCombatHealth(0, creature, COMBAT_PHYSICALDAMAGE, -60, -60)
	elseif item:getId() == 3482 then
		if not creature:isPlayer() then
			doTargetCombatHealth(0, creature, COMBAT_PHYSICALDAMAGE, -30, -30)
		else
			position:sendMagicEffect(CONST_ME_POFF)
		end
		item:transform(3481, 1)
		item:decay()
	elseif item:getId() == 3944 then
		doTargetCombatHealth(0, creature, COMBAT_PHYSICALDAMAGE, -30, -30)
		item:transform(3945, 1)
		item:decay()
	end
end
