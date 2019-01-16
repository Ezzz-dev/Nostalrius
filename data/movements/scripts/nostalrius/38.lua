function onStepIn(creature, item, position, fromPosition)
	if creature:isPlayer() and creature:getPlayer():getStorageValue(8) == 0 then 
		creature:getPlayer():setStorageValue(8, 1)
	end
	Game.sendMagicEffect(item:getPosition(), 15)
end

function onAddItem(item, tileitem, position)
	Game.sendMagicEffect(item:getPosition(), 15)
end
