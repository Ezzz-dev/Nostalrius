function onStepIn(creature, item, position, fromPosition)
	if creature:isPlayer() and creature:getPlayer():getStorageValue(41) < 1 then 
		creature:getPlayer():setStorageValue(41,1)
		Game.sendMagicEffect({x = 32477, y = 31900, z = 01}, 7)
	end
end
