function onStepIn(creature, item, position, fromPosition)
	doRelocate(item:getPosition(),{x = 32281, y = 32389, z = 10})
	item:getPosition():sendMagicEffect(15)
	Game.sendMagicEffect({x = 32281, y = 32389, z = 10}, 15)
end

function onAddItem(item, tileitem, position)
	doRelocate(item:getPosition(),{x = 32281, y = 32389, z = 10})
	item:getPosition():sendMagicEffect(15)
	Game.sendMagicEffect({x = 32281, y = 32389, z = 10}, 15)
end
