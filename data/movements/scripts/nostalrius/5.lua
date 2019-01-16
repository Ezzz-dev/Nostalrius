function onStepIn(creature, item, position, fromPosition)
	if creature:isPlayer() and creature:getPlayer():getStorageValue(48) < 1 then 
		creature:getPlayer():setStorageValue(48,1)
		Game.sendMagicEffect({x = 32549, y = 32142, z = 07}, 15)
	end
end
