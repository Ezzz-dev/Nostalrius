function onStepIn(creature, item, position, fromPosition)
	if creature:isPlayer() and creature:getPlayer():getStorageValue(220) < 1 then 
		creature:getPlayer():setStorageValue(220,1)
	end
end
