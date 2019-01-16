function onStepIn(creature, item, position, fromPosition)
	doRelocate(item:getPosition(),{x = 33231, y = 32705, z = 08})
	item:getPosition():sendMagicEffect(11)
	Game.sendMagicEffect({x = 33231, y = 32705, z = 08}, 11)
end

function onAddItem(item, tileitem, position)
	doRelocate(tileitem:getPosition(),{x = 33231, y = 32705, z = 08})
	tileitem:getPosition():sendMagicEffect(11)
	Game.sendMagicEffect({x = 33231, y = 32705, z = 08}, 11)
end
