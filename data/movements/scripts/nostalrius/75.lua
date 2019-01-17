function onStepIn(creature, item, position, fromPosition)
	if creature:isPlayer() and creature:getPlayer():getItemCount(3238) >= 1 and creature:getPlayer():getStorageValue(262) == 0 then 
		doRelocate(item:getPosition(),{x = 33349, y = 32830, z = 14})
		item:getPosition():sendMagicEffect(11)
		Game.sendMagicEffect({x = 33349, y = 32830, z = 14}, 11)
		creature:getPlayer():removeItem(3238, 1)
	else
		doRelocate(item:getPosition(),{x = 33280, y = 32740, z = 10})
		item:getPosition():sendMagicEffect(11)
		Game.sendMagicEffect({x = 33280, y = 32740, z = 10}, 11)
	end
end

function onAddItem(item, tileitem, position)
	doRelocate(tileitem:getPosition(),{x = 33280, y = 32740, z = 10})
	tileitem:getPosition():sendMagicEffect(11)
	Game.sendMagicEffect({x = 33280, y = 32740, z = 10}, 11)
end
