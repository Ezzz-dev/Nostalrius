function onStepIn(creature, item, position, fromPosition)
	if creature:isPlayer() and creature:getPlayer():getStorageValue(10) == 0 and Game.isItemThere({x = 32309, y = 31975, z = 13},1996) and Game.isItemThere ({x = 32309, y = 31976, z = 13},1996) and Game.isItemThere ({x = 32311, y = 31975, z = 13},1996) and Game.isItemThere ({x = 32311, y = 31976, z = 13},1996) and Game.isItemThere ({x = 32313, y = 31975, z = 13},1998) and Game.isItemThere ({x = 32313, y = 31976, z = 13}, 1998) then 
		Game.sendMagicEffect({x = 32311, y = 31978, z = 13}, 7)
		creature:getPlayer():setStorageValue(10,1)
		doRelocate(item:getPosition(),{x = 32261, y = 31856, z = 15})
		Game.sendMagicEffect({x = 32261, y = 31856, z = 15}, 14)
	else
		doRelocate(item:getPosition(),{x = 32311, y = 31977, z = 13})
		Game.sendMagicEffect({x = 32311, y = 31977, z = 13}, 1)
		doTargetCombatHealth(0, creature, COMBAT_FIREDAMAGE, -250, -250)
	end
end
