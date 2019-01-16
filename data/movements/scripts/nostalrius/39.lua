function onStepIn(creature, item, position, fromPosition)
	if creature:isPlayer() and creature:getPlayer():getStorageValue(8) ~= 0 then 
		Game.sendMagicEffect(item:getPosition(), 15)
	else
		Game.sendMagicEffect(item:getPosition(), 14)
	end
end

function onAddItem(item, tileitem, position)
	Game.sendMagicEffect(item:getPosition(), 14)
end
