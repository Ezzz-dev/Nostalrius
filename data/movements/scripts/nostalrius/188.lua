function onStepIn(creature, item, position, fromPosition)
	if creature:isPlayer() and creature:getPlayer():getStorageValue(5) == 0 then 
		Game.createMonster("ghost", {x = 32275, y = 31901, z = 13})
		Game.createMonster("ghost", {x = 32276, y = 31905, z = 13})
		creature:getPlayer():setStorageValue(5,1)
		doRelocate(item:getPosition(),{x = 32266, y = 31849, z = 15})
		Game.sendMagicEffect({x = 32266, y = 31849, z = 15}, 14)
		Game.createMonster("demon skeleton", {x = 32275, y = 31903, z = 13})
	else
		doRelocate(item:getPosition(),{x = 32277, y = 31903, z = 13})
		Game.sendMagicEffect({x = 32277, y = 31903, z = 13}, 1)
		doTargetCombatHealth(0, creature, COMBAT_FIREDAMAGE, -55, -55)
	end
end
