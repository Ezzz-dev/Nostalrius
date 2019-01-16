function onStepIn(creature, item, position, fromPosition)
	if creature:isPlayer() and creature:getPlayer():getStorageValue(8) == 1 and creature:getPlayer():getStorageValue(9) == 0 then
		creature:getPlayer():setStorageValue(9,1)
		doRelocate(item:getPosition(),{x = 32268, y = 31856, z = 15})
		Game.sendMagicEffect({x = 32268, y = 31856, z = 15}, 14)
	else
		doRelocate(item:getPosition(),{x = 32191, y = 31938, z = 14})
		Game.sendMagicEffect({x = 32191, y = 31938, z = 14}, 1)
		doTargetCombatHealth(0, creature, COMBAT_FIREDAMAGE, -55, -55)
	end
end
