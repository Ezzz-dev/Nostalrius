function onStepIn(creature, item, position, fromPosition)
	doRelocate(item:getPosition(),{x = 33192, y = 32846, z = 08})
	item:getPosition():sendMagicEffect(11)
	Game.sendMagicEffect({x = 33192, y = 32846, z = 08}, 11)
end

function onAddItem(item, tileitem, position)
	doRelocate(item:getPosition(),{x = 33192, y = 32846, z = 08})
	item:getPosition():sendMagicEffect(11)
	Game.sendMagicEffect({x = 33192, y = 32846, z = 08}, 11)
end
