function onStepIn(creature, item, position, fromPosition)
	if creature:isPlayer() and creature:getPlayer():getItemCount(3236) >= 1 and creature:getPlayer():getStorageValue(264) == 0 then
		doRelocate(item:getPosition(),{x = 33146, y = 32666, z = 15})
		item:getPosition():sendMagicEffect(11)
		Game.sendMagicEffect({x = 33146, y = 32666, z = 15}, 11)
		creature:getPlayer():removeItem(3236, 1)
	else
		doRelocate(item:getPosition(),{x = 33206, y = 32592, z = 08})
		item:getPosition():sendMagicEffect(11)
		Game.sendMagicEffect({x = 33206, y = 32592, z = 08}, 11)
	end
end

function onAddItem(item, tileitem, position)
	doRelocate(item:getPosition(),{x = 33206, y = 32592, z = 08})
	item:getPosition():sendMagicEffect(11)
	Game.sendMagicEffect({x = 33206, y = 32592, z = 08}, 11)
end
