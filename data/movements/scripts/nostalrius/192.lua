function onStepIn(creature, item, position, fromPosition)
	if creature:isPlayer() and creature:getPlayer():getStorageValue(6) == 0 then 
		Game.createItem(2121, 1, {x = 32171, y = 31854, z = 15})
		Game.createItem(2121, 1, {x = 32170, y = 31854, z = 15})
		creature:getPlayer():setStorageValue(6,1)
		doRelocate(item:getPosition(),{x = 32272, y = 31849, z = 15})
		Game.sendMagicEffect({x = 32272, y = 31849, z = 15}, 14)
		Game.createItem(2121, 1, {x = 32172, y = 31854, z = 15})
		Game.createItem(2121, 1, {x = 32170, y = 31855, z = 15})
		Game.createItem(2121, 1, {x = 32171, y = 31855, z = 15})
		Game.createItem(2121, 1, {x = 32172, y = 31855, z = 15})
		Game.createItem(2121, 1, {x = 32170, y = 31856, z = 15})
		Game.createItem(2121, 1, {x = 32171, y = 31856, z = 15})
		Game.createItem(2121, 1, {x = 32172, y = 31856, z = 15})
		doTargetCombatHealth(0, creature, COMBAT_EARTHDAMAGE, -33, -33)
	else
		doRelocate(item:getPosition(),{x = 32171, y = 31854, z = 15})
		Game.sendMagicEffect({x = 32171, y = 31854, z = 15}, 1)
		doTargetCombatHealth(0, creature, COMBAT_EARTHDAMAGE, -155, -155)
	end
end
