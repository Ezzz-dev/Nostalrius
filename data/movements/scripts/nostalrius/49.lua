function onStepIn(creature, item, position, fromPosition)
	if creature:isPlayer() and creature:getPlayer():getStorageValue(43) < 1 then 
		creature:getPlayer():setStorageValue(43,1)
		Game.sendMagicEffect({x = 32479, y = 31900, z = 01}, 7)
	end
end
