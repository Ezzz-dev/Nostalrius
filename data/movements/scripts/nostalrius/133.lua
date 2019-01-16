function onStepIn(creature, item, position, fromPosition)
	doRelocate(item:getPosition(),{x = 33280, y = 32744, z = 10})
	item:getPosition():sendMagicEffect(11)
	Game.sendMagicEffect({x = 33280, y = 32744, z = 10}, 11)
end

function onAddItem(item, tileitem, position)
	doRelocate(item:getPosition(),{x = 33280, y = 32744, z = 10})
	item:getPosition():sendMagicEffect(11)
	Game.sendMagicEffect({x = 33280, y = 32744, z = 10}, 11)
end
