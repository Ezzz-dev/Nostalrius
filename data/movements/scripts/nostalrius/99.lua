function onStepIn(creature, item, position, fromPosition)
	doRelocate(item:getPosition(),{x = 33159, y = 32838, z = 08})
	item:getPosition():sendMagicEffect(11)
	Game.sendMagicEffect({x = 33159, y = 32838, z = 08}, 11)
end

function onAddItem(item, tileitem, position)
	doRelocate(item:getPosition(),{x = 33159, y = 32838, z = 08})
	item:getPosition():sendMagicEffect(11)
	Game.sendMagicEffect({x = 33159, y = 32838, z = 08}, 11)
end
