function onStepIn(creature, item, position, fromPosition)
	if creature:isPlayer() and creature:getPlayer():getStorageValue(3) == 0 then 
		Game.createMonster("Warlock", {x = 32216, y = 31841, z = 15})
		Game.createMonster("Warlock", {x = 32216, y = 31834, z = 15})
		creature:getPlayer():setStorageValue(3,1)
	end
end
