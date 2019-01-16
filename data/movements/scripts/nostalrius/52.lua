function onStepIn(creature, item, position, fromPosition)
	if creature:isPlayer() and creature:getPlayer():getStorageValue(42) < 1 then 
		creature:getPlayer():setStorageValue(42, 1)
		Game.sendMagicEffect({x = 32478, y = 31900, z = 01}, 7)
	end
end
